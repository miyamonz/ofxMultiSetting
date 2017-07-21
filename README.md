# ofxMultiSetting

`void T::save(string file)` と `void T::load(string file)` のメンバを持つクラスに対して、

- bin/data
  - base_folder
    - 0.xml
    - 1.xml
    - 2.xml

```ofApp.h
ofxMultiSetting<T> setting;
```

```ofApp.cpp
setting.setup("base_floder");
setting.setCurrentNum(0);
setting.getCurrent().somethingTmethod(); // 0.xmlつかう
setting.save() // => 0.xmlをsave
setting.setCurrentNum(1);
setting.getCurrent().somethingTmethod(); // 1.xmlつかう
setting.save() // => 1.xmlをsave

```

みたいなかんじ
