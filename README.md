# original c++ rendering eingine

**released exe file: https://github.com/sakokazuki/SKRenderer01/releases/tag/0.0.1**
(win x84 build)

## feature
- deferred rendering
- shadow mapping
- physically based rendering
- simple rendering pass system

## todo
- post porocessing
    - antialiasing
    - other effect(ssao, ssr, color correction, exc...)
- script refactaring


## roadmap
### 開発初期 2017.12 ~ 2018.2
日記をみると結構毎日コンスタントにやっていてすごい。  
そもそもc++とopenglの関係すらもわからないままだったので  
ライブラリ入れたり環境調えたり三角形出すのでもかなり精一杯だった。

### ライティング期 2018.2 ~ 2018.6
このあたりからライティング、レンダリングまわりをやっていた。  
ディファードレンダリングとはなにかとか物理ベースレンダリングの理論の勉強とか   
各ライトの実装とか。  
そういうのをやっていくとだんだんレンダリング以外の、c++側のクラスの構成とか  
オブジェクトの値の持ち方が気になってしまってそっちも迷走していた。

### windows期 2018.6 ~ 2018.10
どうやらmacでopenglが非推奨になるらしいということでwindowsを買ってきたり、  
当然そのまま動かなくてやる気になれなかったりしてあんまり手をつけられなくなってきた。
10月くらいにやっとwindowsでみれるようになった。

### 現在
今


## 現状の感想 2019.2
ついにはじめてから1年がたった。  
継続ってなかなかできない。他のこともやりたいし。  
このプロジェクトに関しては目指す目標が高くて何からやればよくわからなくなってきたのが本音。  
ずっと1人でやってたらあっという間に時が過ぎそう。  
ちょっとこれで一区切りにしてみようかと。
