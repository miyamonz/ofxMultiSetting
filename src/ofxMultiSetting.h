#pragma once
#include "ofMain.h"

#define HAS_METHOD(FUNC_NAME) \
template<typename T> \
class has_method_##FUNC_NAME { \
private: template<typename U> \
  static auto check( U v ) -> decltype( v.FUNC_NAME (""), std::true_type() ); \
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
  
  string getPathByNum(int i) {
      return baseFolder+"/setting"+ofToString(settingNum)+".xml";
  }
  T getSettingByNum(int i) {
    T setting;
    setting.load(getPathByNum(i));
  }
  
  void add() {
    settingNum.setMax(settingNum.getMax()+1);
    settingNum = settingNum.getMax();
    load();
  }
  
  void save(){
    current.save(getPathByNum(getCurrentNum()));
  }
  void load() {
    current.load(getPathByNum(getCurrentNum()));
  }
};

