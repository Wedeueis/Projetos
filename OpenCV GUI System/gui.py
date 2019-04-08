import cv2
import numpy as np
import abc

#Color defs
WHITE   = np.array([255,255,255,255], np.uint8)
BLACK   = np.array([  0,  0,  0,255], np.uint8)
RED     = np.array([  0,  0,255,255], np.uint8)
GREEN   = np.array([  0,255,  0,255], np.uint8)
BLUE    = np.array([255,  0,  0,255], np.uint8)
MAGENTA = np.array([255,  0,255,255], np.uint8)
CYANO   = np.array([255,255,  0,255], np.uint8)
YELLOW  = np.array([0  ,255,255,255], np.uint8)

#mouse callback
def on_mouse(event,x,y,flags,param):
    if event == cv2.EVENT_MOUSEMOVE:
        EventDispatcher().dispatch_event(OnMouseEvent(OnMouseEvent.MOUSE_MOVED, (x, y)))
    if event == cv2.EVENT_MOUSEWHEEL:
        EventDispatcher().dispatch_event(OnMouseEvent(OnMouseEvent.MOUSE_WHEEL, (x, y, param)))
    elif event == cv2.EVENT_LBUTTONDBLCLK:
        EventDispatcher().dispatch_event(OnMouseEvent(OnMouseEvent.MOUSE_LBUTTON_DBLCLICK, (x, y)))
    elif event == cv2.EVENT_LBUTTONDOWN:
        EventDispatcher().dispatch_event(OnMouseEvent(OnMouseEvent.MOUSE_LBUTTON_DOWN, (x, y)))
    elif event == cv2.EVENT_LBUTTONUP:
        EventDispatcher().dispatch_event(OnMouseEvent(OnMouseEvent.MOUSE_LBUTTON_UP, (x, y)))
    elif event == cv2.EVENT_RBUTTONDOWN:
        EventDispatcher().dispatch_event(OnMouseEvent(OnMouseEvent.MOUSE_RBUTTON_DOWN, (x, y)))
    elif event == cv2.EVENT_RBUTTONUP:
        EventDispatcher().dispatch_event(OnMouseEvent(OnMouseEvent.MOUSE_RBUTTON_UP, (x, y)))
    elif event == cv2.EVENT_MBUTTONDOWN:
        EventDispatcher().dispatch_event(OnMouseEvent(OnMouseEvent.MOUSE_WBUTTON_DOWN, (x, y)))
    elif event == cv2.EVENT_MBUTTONUP:
        EventDispatcher().dispatch_event(OnMouseEvent(OnMouseEvent.MOUSE_WBUTTON_UP, (x, y)))

class Keyboard(object):
    #To implement: This key codes are plataform dependent so its better to make diferents mappings for diferent plataform
    KEY_ESC = 27
    KEY_SPACE = 32
    KEY_ENTER = 13
    KEY_DEL = 3014656
    KEY_TAB = 9
    KEY_ARROW_UP = 2492368
    KEY_ARROW_RIGHT = 2555904
    KEY_ARROW_DOWN = 2621440
    KEY_ARROW_LEFT = 22424832
    #Numbers start on 48, so num = keycode - 48
    #capital letters starts at 65 until 90
    #lowercase letters starts at 97 until 122
    
    def __init__(self, app):
        self.app = app

    def update(self):
        key = cv2.waitKey(20) & 0xFF
        if key == -1:
            return
        elif key == Keyboard.KEY_ESC:
            self.app.dispatcher.dispatch_event(OnKeyboardEvent(OnKeyboardEvent.KEYBOARD_KEY_ESC))
        elif key == Keyboard.KEY_SPACE:
            self.app.dispatcher.dispatch_event(OnKeyboardEvent(OnKeyboardEvent.KEYBOARD_KEY_SPACE))
        elif key == Keyboard.KEY_ENTER:
            self.app.dispatcher.dispatch_event(OnKeyboardEvent(OnKeyboardEvent.KEYBOARD_KEY_ENTER))
        elif key == Keyboard.KEY_DEL:
            self.app.dispatcher.dispatch_event(OnKeyboardEvent(OnKeyboardEvent.KEYBOARD_KEY_DEL))
        elif key == Keyboard.KEY_TAB:
            self.app.dispatcher.dispatch_event(OnKeyboardEvent(OnKeyboardEvent.KEYBOARD_KEY_TAB))
        elif key == Keyboard.KEY_ARROW_UP:
            self.app.dispatcher.dispatch_event(OnKeyboardEvent(OnKeyboardEvent.KEYBOARD_KEY_ARROW_UP))
        elif key == Keyboard.KEY_ARROW_RIGHT:
            self.app.dispatcher.dispatch_event(OnKeyboardEvent(OnKeyboardEvent.KEYBOARD_KEY_ARROW_RIGHT))
        elif key == Keyboard.KEY_ARROW_DOWN:
            self.app.dispatcher.dispatch_event(OnKeyboardEvent(OnKeyboardEvent.KEYBOARD_KEY_ARROW_DOWN))
        elif key == Keyboard.KEY_ARROW_LEFT:
            self.app.dispatcher.dispatch_event(OnKeyboardEvent(OnKeyboardEvent.KEYBOARD_KEY_ARROW_LEFT))
        else:
            self.app.dispatcher.dispatch_event(OnKeyboardEvent(OnKeyboardEvent.KEYBOARD_KEY_PRESSED, key))

class Event(object):
    def __init__(self, event_type, data=None):
        self._type = event_type
        self._data = data

    @property
    def type(self):
        return self._type

    @property
    def data(self):
        return self._data

class OnMouseEvent(Event):
    MOUSE_LBUTTON_DBLCLICK = "mouse_left_double_click"
    MOUSE_LBUTTON_DOWN = "mouse_left_down"
    MOUSE_LBUTTON_UP = "mouse_left_up"
    MOUSE_RBUTTON_DOWN = "mouse_right_down"
    MOUSE_RBUTTON_UP = "mouse_right_up"
    MOUSE_WBUTTON_DOWN = "mouse_wheel_down"
    MOUSE_WBUTTON_UP = "mouse_wheel_up"
    MOUSE_MOVED = "mouse_move"
    MOUSE_WHEEL = "mouse_wheel"

class IMouseListener(object, metaclass = abc.ABCMeta):
    @abc.abstractclassmethod
    def on_mouse_event(event):
        raise NotImplementedError('users must define on_mouse_event() to use this base class')

class OnKeyboardEvent(Event):
    KEYBOARD_KEY_PRESSED = "key_pressed"
    KEYBOARD_KEY_ESC = "key_esc"
    KEYBOARD_KEY_SPACE = "key_space"
    KEYBOARD_KEY_ENTER = "key_enter"
    KEYBOARD_KEY_DEL = "key_del"
    KEYBOARD_KEY_TAB = "key_tab"
    KEYBOARD_KEY_ARROW_UP = "key_up"
    KEYBOARD_KEY_ARROW_RIGHT = "key_right"
    KEYBOARD_KEY_ARROW_DOWN = "key_down"
    KEYBOARD_KEY_ARROW_LEFT = "key_left"

class IKeyboardListener(object, metaclass = abc.ABCMeta):
    @abc.abstractclassmethod
    def on_keyboard_event(event):
        raise NotImplementedError('users must define on_keyboard_event() to use this base class')

class Singleton(type):
    _instances = {}
    def __call__(cls, *args, **kwargs):
        if cls not in cls._instances:
            cls._instances[cls] = super(Singleton, cls).__call__(*args, **kwargs)
        return cls._instances[cls]

class EventDispatcher(object, metaclass = Singleton):
    def __init__(self):
        self._events = dict()

    def __del__(self):
        self._events = None

    def has_listener(self, event_type, listener):
        if event_type in self._events.keys():
            return listener in self._events[event_type]
        else:
            return False

    def dispatch_event(self, event):
        if event.type in self._events.keys():
            listeners = self._events[event.type]

            for listener in listeners:
                listener(event)

    def add_event_listener(self, event_type, listener):
        if not self.has_listener(event_type, listener):
            listeners = self._events.get(event_type, [])

            listeners.append(listener)

            self._events[ event_type ] = listeners

    def remove_event_listener(self, event_type, listener):
        if self.has_listener( event_type, listener ):
            listeners = self._events[ event_type ]

            if len( listeners ) == 1:
                del self._events[ event_type ]
            else:
                listeners.remove(listener)
                self._events[ event_type ] = listeners


class App(IKeyboardListener):
    def __init__(self):
        self.dispatcher = EventDispatcher()
        self.window = Window("MyGame", 800, 600, self)
        self.keyboard = Keyboard(self)
        self.entities = []
        self.quit = False

        self.dispatcher.add_event_listener(OnKeyboardEvent.KEYBOARD_KEY_ESC, self.on_keyboard_event)

    def add_entity(self, ent):
        self.entities.append(ent)

    def draw(self):
        for ent in self.entities:
            ent.draw(self.window.drawer)
        self.window.draw()

    def update(self):
        self.window.update()
        self.keyboard.update()
        for ent in self.entities:
            ent.update()

    def on_keyboard_event(self, event):
        self.quit = True

    def run(self):
        while(not self.quit):
            self.update()
            self.draw()
        
        cv2.destroyAllWindows()

class Window(IMouseListener):    
    def __init__(self, name, width, height, app):
        self.name = name
        self.width = width
        self.height = height
        self.background_color = WHITE

        self.cursor = [0, 0]

        self.drawer = Drawer(self)
        
        self.app = app
        self.app.dispatcher.add_event_listener(OnMouseEvent.MOUSE_MOVED, self.on_mouse_event)

        cv2.namedWindow(self.name, cv2.WINDOW_NORMAL)
        cv2.resizeWindow(self.name, self.width, self.height)
        cv2.setMouseCallback(self.name, on_mouse)

    def draw(self):
        self.drawer.draw()

    def update(self):
        pass

    def on_mouse_event(self, event):
        if event.type == OnMouseEvent.MOUSE_MOVED:
            self.cursor[0] = event.data[0]
            self.cursor[1] = event.data[1]

class Drawer(object):
    def __init__(self, window):
        self.window = window

        self.canvas = Canvas(self.window.width, self.window.height, self.window.background_color)
        self.buffer = Canvas(self.window.width, self.window.height, self.window.background_color)

    def draw(self):
        self.flip()
        cv2.imshow(self.window.name, self.canvas.get_image())

    def flip(self):
        self.canvas.image = self.buffer.image.copy()
        self.clear()

    def clear(self):
        self.buffer.clear(self.window.background_color)

    def submit(self, img, x, y):
        self.buffer.paint(img, x, y)

    def drawText(self, text, x, y, font=cv2.FONT_HERSHEY_SIMPLEX, scale=1.0, color=(0,0,0,0), thickness=2):
         cv2.putText(self.buffer.image, text, (x, y), font, scale, (0,0,0,0), thickness)

class Canvas(object):
    def __init__(self, width, height, color):
        self.width = width
        self.height = height
        self.image = np.ones( (self.height, self.width, 4), np.uint8) *color

    def get_image(self):
        return self.image

    def clear(self, color):
        self.image = (np.ones( (self.height, self.width, 4), np.uint8) * color).copy()

    def paint(self, img, x, y):
        h, w, c = img.shape
        delta_x = int(x+w)
        delta_y = int(y+h)

        if w > self.width or h > self.height:
            print("canvas: wrong shape!")
            return
        elif (x + w) > (self.width) or x < 0:
            print("canvas: horizontal boundery overflow!")
            return
        elif (y + h) > (self.height) or y < 0:
            print("canvas: vertical boundery overflow!")
            return
        elif c == 3:
            self.image[int(y):delta_y, int(x):delta_x, :3] = img.copy()[:,:,:]
        elif c ==4:
            alpha = img[:,:,3].copy().astype(float)/255
            alpha = np.stack((alpha,)*3, -1)

            foreground = img[:,:,:3].astype(float)
            background = self.image[int(y):delta_y, int(x):delta_x, :3].astype(float)

            foreground = cv2.multiply(alpha, foreground)
            background = cv2.multiply(1.0 - alpha, background)

            self.image[int(y):delta_y, int(x):delta_x, :3]  = cv2.add(foreground, background).astype(np.uint8)
            #self.image[int(y):delta_y, int(x):delta_x, :] = img.copy(where = img[:,:,3])[:,:,:]

class BoundingBox(object):
    def __init__(self, x, y, width, height):
        self.position = (x, y)
        self.size = (width, height)
        self.x = x
        self.y = y
        self.width = width
        self.height = height

    def contains(self, x, y):
        if self.x < x and x < (self.x + self.width) and self.y < y and y < (self.y + self.height):
            return True
        else:
            return False

    def moveTo(self, x, y):
        self.x = x
        self.y = y
        self.position = (x, y)

class IDrawable(object, metaclass=abc.ABCMeta):
    def __init__(self, x, y, width, height, color=MAGENTA):
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.color = color

    @abc.abstractmethod
    def draw(self, drawer):
        raise NotImplementedError('users must define draw to use this base class')

class Image(IDrawable):
    def __init__(self, path="", data = None, x=0, y=0):
        self.data = None
        if data is not None:
            self.data = data
        else:
            self.data = cv2.imread(path, cv2.IMREAD_UNCHANGED)

        [h,w,c] = self.data.shape
        IDrawable.__init__(self, x, y, w, h)
        self.channels = c

    def draw(self, drawer):
        drawer.submit(self.data, self.x, self.y)
    
    def resize(self, width, height):
        self.width = width
        self.height = height
        self.data = cv2.resize(self.data, (width, height), interpolation = cv2.INTER_CUBIC)

    def set_image(self, img):
        self.data = img.data.copy()
        [h,w,c] = self.data.shape
        self.width = w
        self.height = h
        self.channels = c

class Widget(IDrawable):
    def __init__(self, app, x, y, width, height, father=None, color= MAGENTA, img_path = ""):
        IDrawable.__init__(self, x, y, width, height, color)
            
        self.app = app

        if father == None:
            self.father = self

        self.bounds = BoundingBox(x, y, width, height)

        self.active = True
        self.focused = False

    def update(self):
        pass

class Label(Widget):
    def __init__(self, app, x, y, father, text="", color=BLACK, scale = 1.0):
        self.font_scale = scale
        self.margin = 5
        self.thickness = 2
        self.font = cv2.FONT_HERSHEY_SIMPLEX
        self.text = text

        size = cv2.getTextSize(self.text, self.font, self.font_scale, self.thickness)

        width = size[0][0]
        height = size[0][1]
        self.line_height = height + int(size[1]/2) + self.margin

        new_x = x + self.margin
        new_y = y + self.line_height 
        Widget.__init__(self, app, new_x, new_y, width, height, father, color)

    def draw(self, drawer):
        drawer.drawText(self.text, self.x, self.y, scale=self.font_scale, color=self.color, thickness=self.thickness)

    '''
        def _stampText(image, text, line):
		font = cv2.FONT_HERSHEY_SIMPLEX
		font_scale = 0.55
		margin = 5
		thickness = 2
		color = (255, 255, 255)

		size = cv2.getTextSize(text, font, font_scale, thickness)

		text_width = size[0][0]
		text_height = size[0][1]
		line_height = text_height + size[1] + margin
		
		x = image.shape[1] - margin - text_width
		y = margin + size[0][1] + line * line_height
		
		cv2.putText(image, text, (x, y), font, font_scale, color, thickness)
    '''

class Button(Widget, IMouseListener):
    ACTIVE = "button active"
    FOCUSED = "button focused"
    PRESSED = "button pressed"
    DISABLED = "button disabled"

    def __init__(self, app, x, y, width, height, father, text = "",  color = MAGENTA, img_path = "", on_action = None):
        Widget.__init__(self, app, x, y, width, height, father, color, img_path)

        self.state = Button.ACTIVE

        self.active_img = None
        self.focused_img = None
        self.pressed_img = None
        self.disabled_img = None
        self.selected_img = None

        if img_path != "":
            self.active_img = Image(path=img_path, x= self.x, y= self.y)
            self.active_img.resize(self.width, self.height)
            self.selected_img = Image(path=img_path, x=self.x, y=self.y)
            self.selected_img.resize(self.width, self.height)
            self.focused_img = Image(path=img_path, x= self.x, y= self.y)
            self.focused_img.resize(self.width, self.height)
            self.pressed_img = Image(path=img_path, x= self.x, y= self.y)
            self.pressed_img.resize(self.width, self.height)
            self.disabled_img = Image(path=img_path, x= self.x, y= self.y)
            self.disabled_img.resize(self.width, self.height)
        else:
            self.active_img = Image(data= np.ones( (self.height, self.width, 4) , np.uint8)*self.color, x =self.x, y = self.y)
            self.selected_img = Image(data= np.ones( (self.height, self.width, 4) , np.uint8)*self.color, x =self.x, y = self.y)
            self.focused_img = Image(data= np.ones( (self.height, self.width, 4) , np.uint8)*self.color, x =self.x, y = self.y)
            self.pressed_img = Image(data= np.ones( (self.height, self.width, 4) , np.uint8)*self.color, x =self.x, y = self.y)
            self.disabled_img = Image(data= np.ones( (self.height, self.width, 4) , np.uint8)*self.color, x =self.x, y = self.y)
        
        self.label = Label(self.app, self.x + 50, self.y, self, text)

        self.on_action = None

        self.app.dispatcher.add_event_listener(OnMouseEvent.MOUSE_LBUTTON_UP, self.on_mouse_event)
        self.app.dispatcher.add_event_listener(OnMouseEvent.MOUSE_MOVED, self.on_mouse_event)
        self.app.dispatcher.add_event_listener(OnMouseEvent.MOUSE_LBUTTON_DOWN, self.on_mouse_event)

    def set_image(self, state, img_path="", color= MAGENTA):
        img = Image(data= np.ones( (self.height, self.width, 4), np.uint8 )*color, x =self.x, y = self.y)
        if img_path != "":
            img.set_image(Image(path=img_path, x= self.x, y= self.y))
            img.resize(self.width, self.height)

        if state == Button.ACTIVE:
            self.active_img.set_image(img)
        elif state == Button.FOCUSED:
            self.focused_img.set_image(img)
        elif state == Button.PRESSED:
            self.pressed_img.set_image(img)
        elif state == Button.DISABLED:
            self.disabled_img.set_image(img)

    def on_mouse_event(self, event):
        if event.type == OnMouseEvent.MOUSE_MOVED:
            if self.bounds.contains(event.data[0], event.data[1]):
                self.state = Button.FOCUSED
                self.selected_img.set_image(self.focused_img)
            else:
                self.state = Button.ACTIVE
                self.selected_img.set_image(self.active_img)
        if event.type == OnMouseEvent.MOUSE_LBUTTON_DOWN:
            if self.bounds.contains(event.data[0], event.data[1]):
                self.state = Button.PRESSED
                self.selected_img.set_image(self.pressed_img)
                self.on_action()
        if event.type == OnMouseEvent.MOUSE_LBUTTON_UP:
            self.state = Button.FOCUSED
            self.selected_img.set_image(self.focused_img)

    def set_action(self, on_action):
        self.on_action = on_action

    def draw(self, drawer):
        self.selected_img.draw(drawer)
        self.label.draw(drawer)

class Component(Widget):
    def __init__(self):
        self.widgets = []
        self.transformationMatrix = []

    def add_widget(self, widget):
        pass


class Entity(IDrawable):
    def __init__(self, app, x, y, img_path = "" , img = None):
        
        if img is not None:
            self.img = img
        else:
            self.img = Image(img_path, x, y)

        IDrawable.__init__(self, x, y, self.img.width, self.img.height)
        self.app = app

    def update(self):
        delta_x = (self.app.window.cursor[0] - self.x)/10
        delta_y = (self.app.window.cursor[1] - self.y)/10
        self.x += delta_x
        self.y += delta_y
        self.img.x = self.x
        self.img.y = self.y

    def draw(self, drawer):
        self.img.draw(drawer)

if __name__ == '__main__':
    print(__doc__)

    app = App()
    
    ent = Entity(app, 100, 100, img = Image(x= 100, y = 100, data = np.zeros( (50,30,3), np.uint8)))

    btn = Button(app,280,400,200,50, app,"teste", img_path='resources/button_active.png')
    btn.set_image(Button.FOCUSED,  img_path='resources/button_focused.png')
    btn.set_image(Button.PRESSED,  img_path='resources/button_pressed.png')
    def on_action():
        print("Clicou")
    btn.set_action(on_action)

    app.add_entity(ent)
    app.add_entity(btn)

    app.run()
    