#include "Config.hpp"
#include <algorithm>

using namespace std;
using namespace libconfig;

const char *confFile = CONFIG_FILE_NAME;

static Setting &openConfFile(Config &cfg);
static Setting &openConfFile(Config &cfg) {
	// Read the file. If there is an error, report it and exit.
	try {
	    cfg.readFile(confFile);
	}
	catch(const FileIOException &fioex) {
		cout << "Conf file not found. Creating" << endl;
	//	std::cerr << "I/O error while reading conf file." << std::endl;
	//	return(EXIT_FAILURE);
	}
	catch(const ParseException &pex) {
    	std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
			<< " - " << pex.getError() << std::endl;
		exit(EXIT_FAILURE);
	}

	Setting &root = cfg.getRoot();
	return root;
}

static void writeConfFile(Config &cfg);
static void writeConfFile(Config &cfg) {
	try {
		cfg.writeFile(confFile);
//		cout << "Configurations saved OK." << endl;
	}
	catch(const FileIOException &fioex) {
		cerr << "I/O error while writing file: " << confFile << endl;
		exit(EXIT_FAILURE);
	}
}

/******************************************************************************/
// UNIT
ConfUnit::ConfUnit(void) {
	this->ID          = "";
	this->alias       = "";
	this->serverIP    = "";
	this->bkpServerIP = "";
	this->latitude    = 0.0;
	this->longitude   = 0.0;
	this->address     = "";
}

ConfUnit::~ConfUnit(void) {}

void ConfUnit::save(void) {
	Config cfg;
	Setting &root = openConfFile(cfg);

	if(root.exists("Unit"))
		root.remove("Unit");
		
	root.add("Unit", Setting::TypeGroup);

	Setting &unit = root["Unit"];

	// Create the new Unit entry.
	unit.add("ID",          Setting::TypeString) = this->ID;
	unit.add("alias",       Setting::TypeString) = this->alias;
	unit.add("serverIP",    Setting::TypeString) = this->serverIP;
	unit.add("bkpServerIP", Setting::TypeString) = this->bkpServerIP;
	unit.add("latitude",    Setting::TypeFloat)  = this->latitude;
	unit.add("longitude",   Setting::TypeFloat)  = this->longitude;
	unit.add("address",     Setting::TypeString) = this->address;

	writeConfFile(cfg);
}

void ConfUnit::load(void) {
	Config cfg;
	(void) openConfFile(cfg);

	try {
		cfg.lookupValue("Unit.ID",          this->ID);
		cfg.lookupValue("Unit.alias",       this->alias);
		cfg.lookupValue("Unit.serverIP",    this->serverIP);
		cfg.lookupValue("Unit.bkpServerIP", this->bkpServerIP);
		cfg.lookupValue("Unit.latitude",    this->latitude);
		cfg.lookupValue("Unit.longitude",   this->longitude);
		cfg.lookupValue("Unit.address",     this->address);
	}
	catch(const SettingNotFoundException &nfex) {
		cerr << "Unit info corrupted in configuration file." << endl;
	}
}

/******************************************************************************/
// ConfCamera
ConfCamera::ConfCamera(void) {
	this->ID                 = -1;
	this->unitID             = -1;
	this->alias              = "" ;
	this->north              = -1.0;
	this->physicalParameters = nullptr;
}

ConfCamera::~ConfCamera(void) {
}

void ConfCamera::save(const list<ConfCamera> cameras) {
	Config cfg;
	Setting &root = openConfFile(cfg);

	if(root.exists("Cameras"))
		root.remove("Cameras");
		
	root.add("Cameras", Setting::TypeList);
	Setting &s_cameras = root["Cameras"];
	for(auto _camera:cameras) {
		Setting &s_camera = s_cameras.add(Setting::TypeGroup);

		// Create the new Camera entry.
		s_camera.add("ID",     Setting::TypeInt)    = _camera.ID;
		s_camera.add("unitID", Setting::TypeString) = _camera.unitID;
		s_camera.add("alias",  Setting::TypeString) = _camera.alias;
		s_camera.add("north",  Setting::TypeFloat)  = _camera.north;
	}

	writeConfFile(cfg);
}

void ConfCamera::load(list<ConfCamera> &cameras) {
	Config cfg;
	Setting &root = openConfFile(cfg);

	for(int i = 0; i < root["Cameras"].getLength(); i++) {
		Setting &s_camera = root["Cameras"][i];
		cameras.push_back(ConfCamera());
		try {

			s_camera.lookupValue("ID",     cameras.back().ID);
			s_camera.lookupValue("unitID", cameras.back().unitID);
			s_camera.lookupValue("alias",  cameras.back().alias);
			s_camera.lookupValue("north",  cameras.back().north);
		}
		catch(const SettingNotFoundException &nfex) {
			cerr << "Camera info corrupted in configuration file." << endl;
		}
	}
}

/******************************************************************************/
//ROI
ConfROI::ConfROI(void) {
}

ConfROI::~ConfROI(void) {
}

void ConfROI::save(const list<ConfROI> ROIs) {
	Config cfg;
	Setting &root = openConfFile(cfg);

	if(root.exists("ROIs"))
		root.remove("ROIs");
		
	root.add("ROIs", Setting::TypeList);
	Setting &rois = root["ROIs"];

	for(auto _roi:ROIs) {
		Setting &roi = rois.add(Setting::TypeGroup);
		// Create the new ROI entry.
		roi.add("ID",              Setting::TypeInt)    = _roi.ID;
		roi.add("name",            Setting::TypeString) = _roi.name;
		roi.add("positiveWayName", Setting::TypeString) = _roi.positiveWayName;
		roi.add("negativeWayName", Setting::TypeString) = _roi.negativeWayName;
		//Setting PTS
		Setting &pts = roi.add("PT",	Setting::TypeList);
		for (int i = 0; i < (sizeof(_roi.PTs) / sizeof(_roi.PTs[0])); i++) {
			Setting &edge = pts.add(Setting::TypeArray);
			for (int j = 0; i < (sizeof(_roi.PTs[0])/sizeof(_roi.PTs[0][0])); j++) {
				edge.add(Setting::TypeInt) = _roi.PTs[i][j];
			}	
		}
		//Setting Detection Points
		Setting &dtpts = roi.add("DTPT",	Setting::TypeList);
		for (int i = 0; i < (sizeof(_roi.DTPTs) / sizeof(_roi.DTPTs[0])); i++) {
			Setting &edge = dtpts.add(Setting::TypeArray);
			for (int j = 0; i < (sizeof(_roi.DTPTs[0])/sizeof(_roi.DTPTs[0][0])); j++) {
				edge.add(Setting::TypeInt) = _roi.DTPTs[i][j];
			}	
		}
		roi.add("cameraID",        Setting::TypeInt)    = _roi.cameraID;
	}
	writeConfFile(cfg);
}

void ConfROI::load(list<ConfROI> &ROIs) {
	Config cfg;
	Setting &root = openConfFile(cfg);

	for(int i = 0; i < root["ROIs"].getLength(); i++) {
		Setting &roi = root["ROIs"][i];
		ROIs.push_back(ConfROI());
		try {
			roi.lookupValue("ID",              ROIs.back().ID);
			roi.lookupValue("name",            ROIs.back().name);
			roi.lookupValue("positiveWayName", ROIs.back().positiveWayName);
			roi.lookupValue("negativeWayName", ROIs.back().negativeWayName);

			for(int j = 0; j < roi["PT"].getLength(); j++) {
				Setting &pt = roi["PT"][j];
				ROIs.back().PTs[j][0] = pt[0];
				ROIs.back().PTs[j][1] = pt[1];
			}
			
			for(int j = 0; j < roi["DTPT"].getLength(); j++) {
				Setting &pt = roi["DTPT"][j];
				ROIs.back().DTPTs[j][0] = pt[0];
				ROIs.back().DTPTs[j][1] = pt[1];
			}
			
			roi.lookupValue("cameraID",        ROIs.back().cameraID);
		}
		catch(const SettingNotFoundException &nfex) {
			cerr << "ROI [" << i << "] info corrupted in configuration " <<
				"file."	<< endl;
		}
	}
}

/******************************************************************************/
// ConfEvent
ConfEvent::ConfEvent(void) {
	this->ID          = -1;
	this->processorID = -1;
	this->timestamp   = "";
	this->way         = -9;
	this->blob        = nullptr;
}

ConfEvent::~ConfEvent(void) {
//	free(this->blob);
	this->blob = nullptr;
}

void ConfEvent::save(void) {
	Config cfg;
	Setting &root = openConfFile(cfg);

	if(root.exists("Event"))
		root.remove("Event");
		
	root.add("Event", Setting::TypeGroup);

	Setting &event = root["Event"];

	// Create the new Camera entry.
	event.add("ID",          Setting::TypeInt)    = this->ID;
	event.add("processorID", Setting::TypeInt)    = this->processorID;
	event.add("timestamp",   Setting::TypeString) = this->timestamp;
	event.add("way",         Setting::TypeInt)    = this->way;

	writeConfFile(cfg);
}

void ConfEvent::load(void) {
	Config cfg;
	(void) openConfFile(cfg);

	try {
		cfg.lookupValue("Event.ID",          this->ID);
		cfg.lookupValue("Event.processorID", this->processorID);
		cfg.lookupValue("Event.timestamp",   this->timestamp);
		cfg.lookupValue("Event.way",         this->way);
	}
	catch(const SettingNotFoundException &nfex) {
		cerr << "Event info corrupted in configuration file." << endl;
	}
}

/******************************************************************************/
//Processor
ConfProcessor::ConfProcessor(void) {
	this->ID = -1;
	this->processorType = "";
	this->idROI = -1;
}

ConfProcessor::~ConfProcessor(void) {
}

void ConfProcessor::save(const list<ConfProcessor> processors) {
	Config cfg;
	Setting &root = openConfFile(cfg);
	printf("salvando processors\n");

	if(root.exists("Processors"))
		root.remove("Processors");
		
	root.add("Processors", Setting::TypeList);
	Setting &s_processors = root["Processors"];

	for(auto _processor:processors) {
		Setting &s_processor = s_processors.add(Setting::TypeGroup);
		// Create the new Camera entry.
		s_processor.add("ID",            Setting::TypeInt)    = _processor.ID;
		s_processor.add("processorType", Setting::TypeString) = 
			_processor.processorType;
		s_processor.add("idROI",         Setting::TypeInt)    = _processor.idROI;
	}

	printf("salvou processors\n");
	writeConfFile(cfg);
}

void ConfProcessor::load(list<ConfProcessor> &processors) {
	Config cfg;
	Setting &root = openConfFile(cfg);

	for(int i = 0; i < root["Processors"].getLength(); i++) {
		Setting &s_processors = root["Processors"][i];
		processors.push_back(ConfProcessor());
		try {
			s_processors.lookupValue("ID",               processors.back().ID);
			s_processors.lookupValue("processorType",
					processors.back().processorType);
			s_processors.lookupValue("idROI",            processors.back().idROI);
		}
		catch(const SettingNotFoundException &nfex) {
			cerr << "Processor info corrupted in configuration file." << endl;
		}
	}
}

int ConfProcessor::getProperty(list<ConfProcessor> &processors, std::string property) {
	Config cfg;
	Setting &root = openConfFile(cfg);

	int propertyVal = 0;
	for(int i = 0; i < root["Processors"].getLength(); i++) {
		Setting &s_processors = root["Processors"][i];
		try {
			int id;
			s_processors.lookupValue("ID", id);
			if (id == this->ID) {
				s_processors.lookupValue(property, propertyVal);
				break;
			}
			
		}
		catch(const SettingNotFoundException &nfex) {
			cerr << "Processor info corrupted in configuration file." << endl;
		}
	}
	return propertyVal;
}

/******************************************************************************/
//ProcessorType

ConfProcessorType::ConfProcessorType(void) {
	this->ID   = -1;
	this->name = -1;
}

ConfProcessorType::~ConfProcessorType(void) {
}

void ConfProcessorType::save(void) {
	Config cfg;
	Setting &root = openConfFile(cfg);

	if(root.exists("ProcessorType"))
		root.remove("ProcessorType");
		
	root.add("ProcessorType", Setting::TypeGroup);

	Setting &processorType = root["ProcessorType"];

	// Create the new Camera entry.
	processorType.add("ID",   Setting::TypeInt) = this->ID;
	processorType.add("name", Setting::TypeInt) = this->name;

	writeConfFile(cfg);
}

void ConfProcessorType::load(void) {
	Config cfg;
	(void) openConfFile(cfg);

	try {
		cfg.lookupValue("ProcessorType.ID",   this->ID);
		cfg.lookupValue("ProcessorType.name", this->name);
	}
	catch(const SettingNotFoundException &nfex) {
		cerr << "ProcessorType info corrupted in configuration file." << endl;
	}
}

/******************************************************************************/
// CONFIG
Conf::Conf(void) {}
Conf::~Conf(void) {}

void Conf::save(void) {
	this->unit.save();
	ConfCamera::save(this->cameras);
	ConfROI::save(this->ROIs);
	this->event.save();
	ConfProcessor::save(this->processors);
	this->processorType.save();
}

void Conf::load(void) {
	this->unit.load();
	ConfCamera::load(this->cameras);
	ConfROI::load(this->ROIs);
	this->event.load();
	ConfProcessor::load(this->processors);
	this->processorType.load();
}
/*----------------------------------------------------------------------------*/
// UNIT
// setters
void          Conf::unitID(const string ID)   { this->unit.ID = ID; }
void    Conf::unitAlias(const string alias)   { this->unit.alias = alias; }
void    Conf::unitServerIP(const string IP)   { this->unit.serverIP = IP; }
void Conf::unitBkpServerIP(const string IP)   { this->unit.bkpServerIP = IP; }
void    Conf::unitLatitude(const float lat)   { this->unit.latitude = lat; }
void   Conf::unitLongitude(const float lon)   { this->unit.longitude = lon; }
void     Conf::unitAddress(const string addr) { this->unit.address = addr; }
// getters
string          Conf::unitID(void) { return this->unit.ID; }
string       Conf::unitAlias(void) { return this->unit.alias; }
string    Conf::unitServerIP(void) { return this->unit.serverIP; }
string Conf::unitBkpServerIP(void) { return this->unit.bkpServerIP; }
float     Conf::unitLatitude(void) { return this->unit.latitude; }
float    Conf::unitLongitude(void) { return this->unit.longitude; }
string     Conf::unitAddress(void) { return this->unit.address; }

/*----------------------------------------------------------------------------*/
// CAMERA
void Conf::newCamera(void) { this->cameras.push_back(ConfCamera()); }
int  Conf::lenCamera(void) { return this->cameras.size(); }
ConfCamera &Conf::searchCamera(const int id) {
	int i = 0;
	for (auto &&_camera:this->cameras) {
		if(i++ == id) {
			return _camera;
		}
	}
	cerr << "No camera " << id << " found." << endl;
	exit(EXIT_FAILURE);
}
// setters
void Conf::cameraID(const int id, const int ID) {
	this->searchCamera(id).ID = ID;
}
void Conf::cameraUnitID(const int id, const string ID) {
	this->searchCamera(id).unitID = ID;
}
void Conf::cameraAlias(const int id, const string alias) {
	this->searchCamera(id).alias = alias;
}
void  Conf::cameraNorth(const int id, const float north) {
	this->searchCamera(id).north = north;
}
//void Conf::cameraPhysicalParameters(const void *physicalParameters) {
//	ConfCamera _roi = this->searchROI(id);
//	this->camera.physicalParameters = (void *) physicalParameters; } //XXX
// getters
int Conf::cameraID(const int id) {
	return this->searchCamera(id).ID;
}
string Conf::cameraUnitID(const int id) {
	return this->searchCamera(id).unitID;
}
string Conf::cameraAlias(const int id) {
	return this->searchCamera(id).alias;
}
float  Conf::cameraNorth(const int id) {
	return this->searchCamera(id).north;
}
//void *Conf::cameraPhysicalParameters(void) {
//	return this->camera.physicalParameters; } //XXX

/*----------------------------------------------------------------------------*/
// ROI
void Conf::newROI(void) { this->ROIs.push_back(ConfROI()); }
int  Conf::lenROI(void) { return this->ROIs.size(); }
ConfROI &Conf::searchROI(const int id) {
	int i = 0;
	for (auto &&_roi:this->ROIs) {
		if(i++ == id) {
			return _roi;
		}
	}
	cerr << "No roi " << id << " found." << endl;
	exit(EXIT_FAILURE);
}
// setters
void Conf::roiID(const int id, const int ID) {
	this->searchROI(id).ID = ID;
}
void Conf::roiName(const int id, const string name) {
	this->searchROI(id).name = name;
}
void Conf::roiPositiveWayName(const int id, const string positiveWayName) {
	this->searchROI(id).positiveWayName = positiveWayName;
}
void Conf::roiNegativeWayName(const int id, const string negativeWayName) {
	this->searchROI(id).negativeWayName = negativeWayName;
}
#include <string.h>
void Conf::roiSetPTs(const int id, const int PTs[4][2]) {
	ConfROI &_roi = this->searchROI(id);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			_roi.PTs[i][j] = PTs[i][j];
		}
	};
}
void Conf::roiSetDTPTs(const int id, const int PTs[2][2]) {
	ConfROI &_roi = this->searchROI(id);
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			_roi.DTPTs[i][j] = PTs[i][j];
		}
	};
}
void Conf::roiCameraID(const int id, const int cameraID) {
	this->searchROI(id).cameraID = cameraID;
}
// getters
int Conf::roiID(const int id) {
	return this->searchROI(id).ID;
}
string Conf::roiName(const int id) {
	return this->searchROI(id).name;
}
string Conf::roiPositiveWayName(const int id) {
	return this->searchROI(id).positiveWayName;
}
string Conf::roiNegativeWayName(const int id) {
	return this->searchROI(id).negativeWayName;
}
void Conf::roiGetPTs(const int id, int PTs[4][2]) {
	ConfROI &_roi = this->searchROI(id);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			PTs[i][j] = _roi.PTs[i][j];
		}
	}
}
void Conf::roiGetDTPTs(const int id, int PTs[2][2]) {
	ConfROI &_roi = this->searchROI(id);
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			PTs[i][j] = _roi.DTPTs[i][j];
		}
	};
}
int Conf::roiCameraID(const int id) {
	return this->searchROI(id).cameraID;
}

/*----------------------------------------------------------------------------*/
// EVENT
// setters
void                Conf::eventID(const int ID) { this->event.ID = ID; }
void       Conf::eventProcessorID(const int ID) { this->event.processorID = ID;}
void      Conf::eventTimeStamp(const string ts) { this->event.timestamp = ts; }
void              Conf::eventWay(const int way) { this->event.way = way; }
void Conf::eventBlob(const void *blob) { this->event.blob = (void *) blob; }
// getters
int              Conf::eventID(void) { return this->event.ID; }
int     Conf::eventProcessorID(void) { return this->event.processorID; }
string    Conf::eventTimeStamp(void) { return this->event.timestamp; }
int Conf::eventWay(void)             { return this->event.way; }
void *Conf::eventBlob(void) { return this->event.blob; }

/*----------------------------------------------------------------------------*/
// PROCESSOR
void Conf::newProcessor(void) { this->processors.push_back(ConfProcessor()); }
int  Conf::lenProcessor(void) { return this->processors.size(); }
ConfProcessor &Conf::searchProcessor(const int id) {
	int i = 0;
	for (auto &&_processor:this->processors) {
		if(i++ == id) {
			return _processor;
		}
	}
	cerr << "No processor " << id << " found." << endl;
	exit(EXIT_FAILURE);
}
// setters
void Conf::processorID(const int id, const int ID) {
	this->searchProcessor(id).ID = ID;
}
void Conf::processorProcessorType(const int id, const string processorType) {
	this->searchProcessor(id).processorType = processorType;
}
void Conf::processorIdROI(const int id, const int idROI) {
	this->searchProcessor(id).idROI = idROI;
}
// getters
int Conf::processorID(const int id) {
	return this->searchProcessor(id).ID;
}
string Conf::processorProcessorType(const int id) {
	return this->searchProcessor(id).processorType;
}
int Conf::processorIdROI(const int id) {
	return this->searchProcessor(id).idROI;
}

int Conf::processorIntConf(const int id, std::string propertyName) {
	auto processor = this->searchProcessor(id);
	return processor.getProperty(this->processors, propertyName);
}

/*----------------------------------------------------------------------------*/
// PROCESSOR_TYPE
// setters
void Conf::processorTypeID(const int ID) { this->processorType.ID = ID; }
void Conf::processorTypeName(const int name) { this->processorType.name = name;}
// getters
int Conf::processorTypeID(void) { return this->processorType.ID; }
int Conf::processorTypeName(void) { return this->processorType.name; }
