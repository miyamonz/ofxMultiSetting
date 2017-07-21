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

## todo
- ファイル名を数字で判定するのをいい感じに
- addいれる
- コピーとか複製methodつける?
- settingの変更検知 -> ##event検知


## event検知
settingが変更したかどうかを持っていてほしい
変更があったら色をつけて、セーブとか判断しやすくしたい
- そもそもmultiSetting側じゃなくて個別のofParameterとかの責務？ -> multiSetting側は変更があったのboolさえとれればええや
- T::addListener methodを持ってもらう ? Settingクラス側の設計をなるべく要求したくない
  - saveとloadは要求してるけど
  - traitsとか勉強してなんとかなるのでは
addListner or ofEventを要求する感じではいいのでは
