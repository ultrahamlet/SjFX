#include "ofApp.h"
#include <codecvt>
//--------------------------------------------------------------
std::wstring multi_to_wide_capi(std::string const& src)
{
	std::size_t converted{};
	std::vector<wchar_t> dest(src.size(), L'\0');
	if (::_mbstowcs_s_l(&converted, dest.data(), dest.size(), src.data(), _TRUNCATE, ::_create_locale(LC_ALL, "jpn")) != 0) {
		throw std::system_error{ errno, std::system_category() };
	}
	dest.resize(std::char_traits<wchar_t>::length(dest.data()));
	dest.shrink_to_fit();
	return std::wstring(dest.begin(), dest.end());
}
std::string wide_to_utf8_cppapi(std::wstring const& src)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.to_bytes(src);
}

std::string multi_to_utf8_cppapi(std::string const& src)
{
	auto const wide = multi_to_wide_capi(src);
	return wide_to_utf8_cppapi(wide);
}

std::string toUtf8(const std::wstring &str)
{
	std::string ret;
	int len = WideCharToMultiByte(CP_UTF8, 0, str.c_str(), str.length(), NULL, 0, NULL, NULL);
	if (len > 0)
	{
		ret.resize(len);
		WideCharToMultiByte(CP_UTF8, 0, str.c_str(), str.length(), &ret[0], len, NULL, NULL);
	}
	return ret;
}
//--------------------------------------------------------------
void ofApp::setup(){
	grabber.setup(ofGetWidth(), ofGetHeight());
	// ====== SPOUT =====
	
	senderwidth = ofGetWidth();
	senderheight = ofGetHeight();
	// Create an RGBA fbo for texture transfers
	spFbo.allocate(senderwidth, senderheight, GL_RGBA);
	oFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	//oFbo.getTextureReference().getTextureData().bFlipTexture = true;
	
	// If no name is specified, the executable name is used.
	sender.SetSenderName(sendername);
	// Update caption in case of multiples of the same sender
	ofSetWindowTitle(sender.GetName());
	//
	// Font setting
	ofTrueTypeFontSettings fsettings("Fonts/meiryo.ttc", 24);
	fsettings.addRanges(ofAlphabet::Emoji);//絵文字
	fsettings.addRanges(ofAlphabet::Japanese);//日本語
	fsettings.addRange(ofUnicode::Space);//スペース
	fsettings.addRange(ofUnicode::IdeographicSpace);//全角スペース
	fsettings.addRange(ofUnicode::Latin);//アルファベット等
	fsettings.addRange(ofUnicode::Latin1Supplement);//記号、アクサン付き文字など
	fsettings.addRange(ofUnicode::NumberForms);//数字？
	fsettings.addRange(ofUnicode::Arrows);//矢印
	fsettings.addRange(ofUnicode::MathOperators);//数式記号
	fsettings.addRange(ofUnicode::Hiragana);//ひらがな
	fsettings.addRange(ofUnicode::Katakana);//カタカナ
	fsettings.addRange(ofUnicode::MiscSymbolsAndPictographs);//絵文字など
	fsettings.addRange(ofUnicode::Emoticons);//エモーティコン
	//settings.addRange(ofUnicode::KatakanaHalfAndFullwidthForms);//エモーティコン
	//
	if (!font.load(fsettings))
		cout << "couldn't load font" << endl;
	//
	// udp connect
	udpConnectionRx.Create();
	udpConnectionRx.Bind(12345); //incomming data on my port # ...  
	udpConnectionRx.SetNonBlocking(true);

	received = false;
	flipY = true;
}

//--------------------------------------------------------------
void ofApp::update(){
	
	grabber.update();

	// UDP 受信
	char data[512];
	//unsigned short int *val;
	udpConnectionRx.Receive(data, 512);
	//std::cout << str << "-" <<  std::endl;
	uint16_t *val = (uint16_t*)data;
	//std::cout << val[0] << std::endl;
	BOOL strOK = true;
	for (int i = 0; i < sizeof(val); i++) {
		if (val[i] < 256) { strOK = false; break; }
	}
	if (strOK) {
		recvStr = data;
		received = true;
		std::cout << recvStr << std::endl;
		// shift-jis -> utf8
		ostr = multi_to_utf8_cppapi(recvStr);
		std::cout <<  "Received" << std::endl;
	}

}

//--------------------------------------------------------------
void ofApp::draw(){

	oFbo.begin();
	
	 ofSetColor(255, 255, 255);
	 
	 grabber.draw(0, 0);
	// font.drawString(u8"漢字テスト", 0, 200);
	 if (received) font.drawString(ostr, 200, ofGetHeight()-30);
	oFbo.end();

	spFbo.begin();    
	//grabber.draw(0, 0);
	if (flipY) {
		ofScale(-1, 1);
		ofTranslate(-ofGetWidth(), 0);
	}
	oFbo.draw(0, 0);
	 sender.SendFbo(oFbo.getId(), senderwidth, senderheight, false);
	spFbo.end();

	oFbo.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

	if (key = ' ') flipY = !flipY;

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
