#include "cinder/app/AppNative.h"
#include "cinder/app/RendererGl.h"
#include "Map.h"
//#include "TemplatedMapProvider.h"
#include "BingMapsProvider.h"
//#include "OpenStreetMapProvider.h"
#include "Transitioner.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace ci::modestmaps;
using namespace std;

class cinder_modestmaps_testApp : public AppNative {
 public:

	void prepareSettings(Settings *settings);
	void setup();
	void update();
	void touchesBegan( TouchEvent event );
	void touchesMoved( TouchEvent event );
	void touchesEnded( TouchEvent event );
	void keyUp( KeyEvent event );
	void mouseDown( MouseEvent event );
	void mouseDrag( MouseEvent event );
	void mouseWheel( MouseEvent event );
	void mouseMove( MouseEvent event );
	void draw();
	//void resize( ResizeEvent event);
	
	Map map;
	vec2 pMouse;
	Transitioner transitioner;
	
	std::map<uint32_t, vec2> prevTouches;
};

void cinder_modestmaps_testApp::prepareSettings(Settings *settings) {
	settings->enableMultiTouch(true);
	settings->setTitle("Modest Maps Cinder - Test App");
}

void cinder_modestmaps_testApp::update() {
	if (transitioner.active) {
		transitioner.update(getElapsedSeconds());	
	}
}

void cinder_modestmaps_testApp::setup()
{
	setFrameRate(60.0);
	//map.setup(new OpenStreetMapProvider(), this->getWindowWidth()/*2.0*/, this->getWindowHeight()/*2.0*/);
	map.setup(BingMapsProvider::create(), vec2(this->getWindowWidth(), this->getWindowHeight()));
	transitioner.setMap(&map);
}

void cinder_modestmaps_testApp::keyUp( KeyEvent event) 
{
	int key = event.getCode();
	if (key == KeyEvent::KEY_LEFT) {
		map.panLeft();
	}
	else if (key == KeyEvent::KEY_RIGHT) {
		map.panRight();
	}
	else if (key == KeyEvent::KEY_UP) {
		map.panUp();
	}
	else if (key == KeyEvent::KEY_DOWN) {
		map.panDown();
	}
	else if (key == KeyEvent::KEY_KP_PLUS || key == KeyEvent::KEY_PLUS || key == KeyEvent::KEY_EQUALS) {
		if (map.getZoom() < 19) {
			map.zoomIn();
		}
	}
	else if (key == KeyEvent::KEY_KP_MINUS || key == KeyEvent::KEY_MINUS || key == KeyEvent::KEY_UNDERSCORE) {
		if (map.getZoom() > 0) {
			map.zoomOut();
		}
	}	
	else if (key == KeyEvent::KEY_f) {
		setFullScreen(!isFullScreen());
	}
	else if (key == KeyEvent::KEY_SPACE) {
		Location l(Rand::randFloat(-85,85), Rand::randFloat(-180,180));
		double z = Rand::randFloat(1, 17);
		transitioner.setTarget(l,z,getElapsedSeconds());		
	}
}

void cinder_modestmaps_testApp::mouseMove( MouseEvent event )
{
	//cout << map.pointLocation(Vec2d(event.getX(), event.getY())) << endl;
}

void cinder_modestmaps_testApp::mouseDown( MouseEvent event )
{
	pMouse = event.getPos();
}

void cinder_modestmaps_testApp::mouseDrag( MouseEvent event )
{
	vec2 diff = vec2(event.getPos().x - pMouse.x, event.getPos().y - pMouse.y);
	map.panBy(diff.x, diff.y);
	pMouse = event.getPos();	
}

void cinder_modestmaps_testApp::mouseWheel( MouseEvent event )
{
	float delta = event.getWheelIncrement();
	vec2 pos = event.getPos();
	if (fabs(delta)) {
		if (event.isShiftDown()) {
			map.rotateBy(delta > 0 ? M_PI/72.0 : -M_PI/72.0, pos.x, pos.y);
		}
		else {
			map.scaleBy(delta > 0 ? 1.05 : 1.0/1.05, pos.x, pos.y);
		}
	}
}

void cinder_modestmaps_testApp::draw()
{
	gl::clear( Color( 1.0f, 1.0f, 1.0f ) );
	
//	double w = this->getWindowWidth();
//	double h = this->getWindowHeight();

//	glPushMatrix();
//	glTranslated(w/4.0, h/4.0, 0);

//	glEnable(GL_SCISSOR_TEST);
//	glScissor(w/4, h/4, w/2, h/2);
		
	map.draw();
	
//	const double polygon[273][2] = {
//        {-72.29496765,41.27000046},{-72.87638092,41.22064972},{-73.70992279,40.93110275},{-72.24116516,41.11948013},{-71.94489288,40.93000031},{-73.34494019,40.63000107},{-73.981987,40.62799835},{-73.9522171,40.7507515},{-74.25659943,40.47351074},{-73.9623642,40.42763138},{-74.17830658,39.70925903},{-74.90597534,38.93954086},{-74.98040771,39.19639969},{-75.20000458,39.24845123},{-75.52797699,39.49850082},{-75.31989288,38.95999908},{-75.08345032,38.78120041},{-75.05667114,38.4041214},{-75.37741089,38.01551056},{-75.94013977,37.21688843},{-76.03122711,37.25659943},{-75.72203827,37.93704987},{-76.23282623,38.31921387},{-76.3499527,39.15000153},{-76.54272461,38.71761322},{-76.32923889,38.08325958},{-76.95992279,38.23288345},{-76.30152893,37.91794586},{-76.25871277,36.96640015},{-75.97180176,36.89725876},{-75.86804199,36.55125046},{-75.72746277,35.55073929},{-76.36313629,34.80854034},{-77.3975296,34.51200867},{-78.05490112,33.92546844},{-78.55429077,33.86132813},{-79.06066895,33.49394989},{-79.20353699,33.15839005},{-80.30121613,32.50935364},{-80.86487579,32.03329849},{-81.3361969,31.44049072},{-81.49041748,30.72999001},{-81.31360626,30.03552055},{-80.97995758,29.18000031},{-80.5355835,28.47212982},{-80.52993774,28.04000092},{-80.05649567,26.87999916},{-80.0880127,26.20576477},{-80.13150024,25.81677437},{-80.38093567,25.20615959},{-80.67998505,25.07999992},{-81.17211151,25.20125961},{-81.32991028,25.63999939},{-81.70992279,25.87000084},{-82.2399826,26.72999954},{-82.70513153,27.49504089},{-82.85518646,27.88624001},{-82.64992523,28.54999924},{-82.92998505,29.10000038},{-83.70948029,29.93655968},{-84.0999527,30.09000015},{-85.10871124,29.63615036},{-85.2878418,29.68611908},{-85.77304077,30.15261078},{-86.39992523,30.39999962},{-87.53031158,30.27433014},{-88.4177475,30.38489914},{-89.18047333,30.31598091},{-89.60491943,30.17635918},{-89.41365814,29.89418983},{-89.42998505,29.48863983},{-89.21763611,29.29108047},{-89.40817261,29.15961075},{-89.77919006,29.30714035},{-90.15457153,29.11742973},{-90.88014984,29.14853477},{-91.62675476,29.67700005},{-92.49898529,29.5522995},{-93.22626495,29.78375053},{-93.84835815,29.71363068},{-94.69000244,29.47999954},{-95.60018158,28.73863029},{-96.59394836,28.30747986},{-97.13990784,27.82999992},{-97.36998749,27.37999916},{-97.37989044,26.69000053},{-97.32991028,26.20999908},{-97.13990784,25.87000084},{-97.52993774,25.84000015},{-98.2399826,26.05999947},{-99.01992035,26.37000084},{-99.29997253,26.84000015},{-99.51992035,27.54000092},{-100.10997009,28.11000061},{-100.45578003,28.69611931},{-100.95755768,29.3807106},{-101.66230774,29.77930069},{-102.47995758,29.76000023},{-103.10997009,28.96999931},{-103.94000244,29.27000046},{-104.45697021,29.57196045},{-104.70574951,30.1217308},{-105.03733826,30.64402008},{-105.6315918,31.08382988},{-106.14286804,31.39995003},{-106.50754547,31.75452042},{-108.2399826,31.7548542},{-108.24194336,31.34222031},{-109.03494263,31.34193993},{-111.02350616,31.33472061},{-113.30488586,32.03913879},{-114.81500244,32.52528},{-114.72135925,32.72082901},{-115.99131775,32.61238861},{-117.12773132,32.53533936},{-117.29586029,33.0462265},{-117.94393921,33.62123489},{-118.41056824,33.74090958},{-118.51989746,34.02778244},{-119.08098602,34.07799911},{-119.43884277,34.34847641},{-120.36769104,34.44710922},{-120.62286377,34.60855103},{-120.7443161,35.15686035},{-121.71450806,36.16152954},{-122.54737854,37.55176163},{-122.51191711,37.78339005},{-122.95317841,38.1137085},{-123.72714233,38.95166016},{-123.86517334,39.76699066},{-124.39807129,40.3132019},{-124.17880249,41.14202118},{-124.21366882,41.99964142},{-124.53283691,42.76599121},{-124.14203644,43.70838165},{-123.89891815,45.5234108},{-124.07954407,46.86474991},{-124.39559174,47.72016907},{-124.68717957,48.18443298},{-124.56610107,48.37971497},{-123.11998749,48.04000092},{-122.58732605,47.09600067},{-122.3399353,47.36000061},{-122.5,48.18000031},{-122.8399353,49.},{-120.,49.},{-117.03116608,49.},{-116.04813385,49.},{-113.,49.},{-110.04997253,49.},{-107.04997253,49.},{-104.048172,48.99985886},{-100.64992523,49.},{-97.22867584,49.0007019},{-95.15904236,49.},{-95.15604401,49.38425064},{-94.81755066,49.38904953},{-94.63990784,48.84000015},{-94.32906342,48.67073822},{-93.63085175,48.60926056},{-92.60997009,48.45000076},{-91.63990784,48.13999939},{-90.82991028,48.27000046},{-89.5999527,48.00999832},{-90.42497253,47.73500824},{-90.61998749,47.68000031},{-91.32991028,47.27999878},{-92.00868225,46.85842133},{-92.01187134,46.71168137},{-91.00989532,46.91999817},{-90.33087158,46.49705505},{-89.3114624,46.79362869},{-88.82253265,47.15478134},{-87.93984985,47.48590851},{-88.26123047,46.95856094},{-87.69425964,46.83103943},{-86.9899826,46.45000076},{-86.10259247,46.67266083},{-85.11998749,46.75999832},{-84.90994263,46.47999954},{-84.60482025,46.4396019},{-84.3366394,46.40877151},{-83.8391571,46.01020813},{-84.71994019,45.91999817},{-84.94374084,45.95002747},{-85.53995514,46.02999878},{-86.31989288,45.83000183},{-87.,45.74000168},{-87.53917694,45.17393112},{-87.98823547,44.73331833},{-87.85274506,44.61503983},{-87.11802673,45.25933075},{-86.96744537,45.26287842},{-87.48629761,44.49335098},{-87.71221924,43.79650879},{-87.9020462,43.23051834},{-87.77672577,42.74087143},{-87.79560852,42.23411942},{-87.52606964,41.70851135},{-87.09439087,41.64617157},{-86.62184143,41.89442062},{-86.21595764,42.38169098},{-86.18839264,43.04140854},{-86.51992035,43.65999985},{-86.47026825,44.08422852},{-86.20935059,44.57477188},{-85.95972443,44.91059875},{-85.55999756,45.15000153},{-85.46699524,44.81459045},{-85.29036713,45.30826187},{-85.06989288,45.40999985},{-84.92998505,45.79000092},{-84.07991028,45.59000015},{-83.3399353,45.20000076},{-83.25878906,44.74571991},{-83.3499527,44.29000092},{-83.89992523,43.88999939},{-83.84867859,43.63830948},{-83.64992523,43.63000107},{-83.02993774,44.06999969},{-82.65994263,43.97000122},{-82.47995758,43.38999939},{-82.42998505,42.97999954},{-82.89992523,42.43000031},{-83.11998749,42.08000183},{-83.41996765,41.72999954},{-82.84604645,41.48711014},{-82.34737396,41.43590927},{-81.62343597,41.56893158},{-81.03118896,41.84550858},{-80.45462036,42.00437164},{-79.76209259,42.26961899},{-78.9005661,42.86671829},{-78.91996765,42.96500015},{-79.00989532,43.27000046},{-78.06989288,43.36999893},{-77.5999527,43.24000168},{-76.92998505,43.25999832},{-76.17998505,43.59000015},{-76.23924255,43.97914886},{-76.375,44.09630966},{-75.31814575,44.81644821},{-74.86688995,45.00048065},{-73.34772491,45.00738144},{-71.50495148,45.0082016},{-71.40493774,45.25500107},{-71.08473206,45.30524063},{-70.65994263,45.45999908},{-70.30498505,45.91500092},{-69.99990845,46.69306946},{-69.2371521,47.44778061},{-68.90493774,47.18500137},{-68.23442841,47.3548584},{-67.79035187,47.06636047},{-67.79129791,45.70280838},{-67.13736725,45.13753128},{-66.96466064,44.80970001},{-68.03242493,44.32519913},{-69.05999756,43.97999954},{-70.11612701,43.68405151},{-70.69000244,43.02999878},{-70.81487274,42.86529922},{-70.8249054,42.33499908},{-70.49498749,41.80500031},{-70.07991028,41.77999878},{-70.18499756,42.14500046},{-69.88492584,41.92282867},{-69.96502686,41.63716888},{-70.63990784,41.47499847},{-71.12033081,41.49444962},{-71.85997009,41.31999969},{-72.29496765,41.27000046},{-72.29496765,41.27000046}
//    };
//	
//	gl::color( Color( 1.0f, 1.0f, 0.0f ) );
//	glBegin(GL_LINE_STRIP);
//	for (int i = 0; i < 273; i++) {
//		Vec2f p = map.locationPoint(Location(polygon[i][1], polygon[i][0]));
//		glVertex2d(p.x, p.y);
//	}	
//	glEnd();

//	glDisable(GL_SCISSOR_TEST);
	
//	glPopMatrix();

	// draw bounding box of map:
/*	gl::color( Color( 0.0f, 1.0f, 0.0f ) );
	glBegin(GL_LINE_STRIP);
	gl::vertex(Vec2f(w/4.0,h/4.0));
	gl::vertex(Vec2f(3.0*w/4.0,h/4.0));
	gl::vertex(Vec2f(3.0*w/4.0,3.0*h/4.0));
	gl::vertex(Vec2f(w/4.0,3.0*h/4.0));
	gl::vertex(Vec2f(w/4.0,h/4.0));
	glEnd(); */
	
	// draw touch points:
	gl::color( Color( 1.0f, 1.0f, 1.0f ) );
	std::vector<TouchEvent::Touch> touches = getActiveTouches();
	for (int i = 0; i < touches.size(); i++) {
		gl::drawStrokedCircle( touches[i].getPos(), 20 );
	}
	
}



void cinder_modestmaps_testApp::touchesBegan( TouchEvent event )
{
	for (int i = 0; i < event.getTouches().size(); i++) {
		prevTouches[event.getTouches()[i].getId()] = event.getTouches()[i].getPos();
	}
}
	
void cinder_modestmaps_testApp::touchesMoved( TouchEvent event )
{
	std::vector<TouchEvent::Touch> touches = getActiveTouches();
	if (touches.size() == 1) {
		vec2 prevTouch = prevTouches[touches[0].getId()];
		map.panBy(touches[0].getX() - prevTouch.x, touches[0].getY() - prevTouch.y);
		prevTouches[touches[0].getId()] = touches[0].getPos();
	}
	if (touches.size() == 2) {
		vec2 p0 = touches[0].getPos();
		vec2 p1 = touches[1].getPos();
		//cout << p0 << " " << p1 << endl;
		/*double startDist = p0.distance(p1);
		vec2 startCenter = p0.lerp(0.5, p1);
		double startRot = atan2(p1.y-p0.y,p1.x-p0.x);
		vec2 p2 = prevTouches[touches[0].getId()];
		vec2 p3 = prevTouches[touches[1].getId()];
		cout << p2 << " " << p3 << endl;
		double endDist = p2.distance(p3);
		vec2 endCenter = p2.lerp(0.5, p3);
		double endRot = atan2(p3.y-p2.y,p3.x-p2.x);
		//////
		double sc = startDist / endDist;
		double r = startRot - endRot;
		map.panBy(startCenter.x-endCenter.x,startCenter.y-endCenter.y);
		map.scaleBy(sc, endCenter.x, endCenter.y);
		map.rotateBy(r, endCenter.x, endCenter.y); */
		//////
		prevTouches[touches[0].getId()] = p0;
		prevTouches[touches[1].getId()] = p1;
	}
}
void cinder_modestmaps_testApp::touchesEnded( TouchEvent event )
{

}
	
/*void cinder_modestmaps_testApp::resize( ResizeEvent event )
{
	map.setSize( event.getWidth(), event.getHeight() );
}*/


// This line tells Cinder to actually create the application
CINDER_APP_NATIVE(cinder_modestmaps_testApp, RendererGl)
