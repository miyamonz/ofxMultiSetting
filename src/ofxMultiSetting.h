#pragma once
#include "ofMain.h"

#define HAS_METHOD(func_name) \
template<typename T> \
class has_method_##func_name { \
private: template<typename U> \
  static auto check( U v ) -> decltype( v.func_name (""), std::true_type() ); \
  static auto check( ... ) -> decltype(  std::false_type() ); \
public: \
  typedef  decltype(check(std::declval<T>())) type; \
  static bool const value = type::value; \
};

HAS_METHOD(save);
HAS_METHOD(load);

template<typename T>
class ofxMultiSetting {
  static_assert(has_method_save<T>::value, "ofxMultiSetting parameter T must have void T::save(string) method");
  static_assert(has_method_load<T>::value, "ofxMultiSetting parameter T must have void T::load(string) method");
public:
  T current;
  ofParameter<int> settingNum;
  string baseFolder;
  ofxMultiSetting() {};
  void setup(string base){
    baseFolder = base;
    ofDirectory dir(base);
    int num = dir.listDir();
    settingNum.set("setting num", 0, 0, num-1);
  }
  
  T& getCurrent() { return current; }
  int  getCurrentNum() { return settingNum; }
  void setCurrentNum(int i) {
    settingNum = ofClamp(i, settingNum.getMin(), settingNum.getMax());
    load();
  }
  void offset(int i) {
    setCurrentNum(getCurrentNum() + i);
  }
  
  T getSettingByNum(int i) {
    T setting;
    setting.load("");
  }
  
  void add() {
    settingNum.setMax(settingNum.getMax()+1);
    settingNum = settingNum.getMax();
    load();
  }
  
  //string getPathByNum(int i) { retrn  }
  void save(){
    current.save(baseFolder+"/setting"+ofToString(settingNum)+".xml");
  }
  void load() {
    current.load(baseFolder+"/setting"+ofToString(settingNum)+".xml");
  }
};

