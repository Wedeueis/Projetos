#ifndef CONF_HPP
#define CONF_HPP

#include <iostream>
#include <cstdlib>
#include <libconfig.h++>
#include <list>

#define CONFIG_FILE_NAME "EOC.cfg"

using namespace std;
using namespace libconfig;

class ConfUnit {
// attributes
private:
public:
	string ID;
	string alias;
	string serverIP;
	string bkpServerIP;
	float  latitude;
	float  longitude;
	string address;

// methods
private:
public:
	ConfUnit(void);
	~ConfUnit(void);

	void save(void);
	void load(void);

};

class ConfCamera {
// attributes
private:
public:
	int    ID;
	string unitID;
	string alias;
	float  north;
	void   *physicalParameters;

// methods
private:
public:
	ConfCamera(void);
	~ConfCamera(void);
	
	static void save(const list<ConfCamera> cameras);
	static void load(list<ConfCamera> &cameras);
};

class ConfROI {
// attributes
private:
public:
	int    ID;
	string name;
	string positiveWayName;
	string negativeWayName;
	int    PTs[4][2];
	int    DTPTs[2][2];
	int	   cameraID;

// methods
private:
public:
	ConfROI(void);
	~ConfROI(void);

	void newROI(void);
	static void save(const list<ConfROI> ROIs);
	static void load(list<ConfROI> &ROIs);
};

// XXX DEPRECATED!!!
class ConfEvent {
// attributes
private:
public:
	int    ID;
	int    processorID;
	string timestamp;
	int    way;
	void   *blob;

// methods
private:
public:
	ConfEvent(void);
	~ConfEvent(void);

	void save(void);
	void load(void);
};

class ConfProcessor {
// attributes
private:
public:
	int    ID;
	string processorType; //we know this should be an ID to another table
	int    idROI;

// methods
private:
public:
	ConfProcessor(void);
	~ConfProcessor(void);

	static void save(const list<ConfProcessor> processors);
	static void load(list<ConfProcessor> &processors);
	int getProperty(list<ConfProcessor> &processors, std::string property);
};

// XXX DEPRECATED!!!
class ConfProcessorType {
// attributes
private:
public:
	int ID;
	int name;

// methods
private:
public:
	ConfProcessorType(void);
	~ConfProcessorType(void);

	void save(void);
	void load(void);
};

/******************************************************************************/

class Conf {
// attributes
private:
	Config cfg;
	Setting &root = cfg.getRoot();

	ConfUnit            unit;
	list<ConfCamera>    cameras;
	list<ConfROI>       ROIs;
	ConfEvent           event;
	list<ConfProcessor> processors;
	ConfProcessorType processorType;

//	bool unitPresence            = false;
//	bool cameraPresence          = false;
//	bool roisPresence            = false;
//	bool eventPresence           = false;
//	bool processorPresence       = false;
//	bool processorTypePresence   = false;
public:

// methods
private:
	ConfCamera       &searchCamera(const int id);
	ConfROI             &searchROI(const int id);
	ConfProcessor &searchProcessor(const int id);
public:
	Conf(void);
	~Conf(void);

	void save(void);
	void load(void);

	// UNIT
	// setters
	void          unitID(const string ID);
	void       unitAlias(const string alias);
	void    unitServerIP(const string serverIP);
	void unitBkpServerIP(const string bkpServerIP);
	void    unitLatitude(const float  latitude);
	void   unitLongitude(const float  longitude);
	void     unitAddress(const string address);
	// getters
	string          unitID(void);
	string       unitAlias(void);
	string    unitServerIP(void);
	string unitBkpServerIP(void);
	float     unitLatitude(void);
	float    unitLongitude(void);
	string     unitAddress(void);

	// CAMERA
	void newCamera(void);
	int  lenCamera(void);
	// setters
	void                 cameraID(const int id, const int ID);
	void             cameraUnitID(const int id, const string unitID);
	void              cameraAlias(const int id, const string alias);
	void              cameraNorth(const int id, const float);
	void cameraPhysicalParameters(const int id, const void *physicalParameters);
	// getters
	int                   cameraID(const int id);
	string            cameraUnitID(const int id);
	string             cameraAlias(const int id);
	float              cameraNorth(const int id);
	void *cameraPhysicalParameters(const int id);

	// ROI
	void newROI(void);
	int  lenROI(void);
	// setters
	// the first parameter, id, tells us which roi should be used from the list.
	void              roiID(const int id, const int ID);
	void            roiName(const int id, const string name);
	void roiPositiveWayName(const int id, const string positiveWayName);
	void roiNegativeWayName(const int id, const string negativeWayName);
	void          roiSetPTs(const int id, const int PTs[4][2]);
	void          roiSetDTPTs(const int id, const int PTs[2][2]);
	void        roiCameraID(const int id, const int cameraID);
	//getters
	int                 roiID(const int id);
	string            roiName(const int id);
	string roiPositiveWayName(const int id);
	string roiNegativeWayName(const int id);
	void            roiGetPTs(const int id, int PTs[4][2]);
	void            roiGetDTPTs(const int id, int PTs[2][2]);
	int           roiCameraID(const int id);

	// EVENT
	// setters
	void          eventID(const int ID);
	void eventProcessorID(const int ID);
	void   eventTimeStamp(const string timestamp);
	void         eventWay(const int way);
	void        eventBlob(const void *blob);
	// getters
	int              eventID(void);
	int     eventProcessorID(void);
	string    eventTimeStamp(void);
	int             eventWay(void);
	void          *eventBlob(void);

	// PROCESSOR
	void newProcessor(void);
	int  lenProcessor(void);
	// setters
	void               processorID(const int id, const int ID);
	void    processorProcessorType(const int id, const string processorType);
	void            processorIdROI(const int id, const int IdROI);
	// getters
	int                  processorID(const int id);
	string    processorProcessorType(const int id);
	int               processorIdROI(const int id);
	int 			  processorIntConf(const int id, std::string name);

	// PROCESSOR_TYPE
	// setters
	void processorTypeID(const int ID);
	void processorTypeName(const int name);
	// getters
	int processorTypeID(void);
	int processorTypeName(void);
	
};

#endif
