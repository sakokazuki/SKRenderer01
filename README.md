
# GAME

## intro

ゲーム業界への転職を考えて、ゲームをつくってみることにした。
windowsで自由に開発ができる環境が今ないのでひとまず
macをつかってXCodeで開発をすすめる。

C++もopenFrameworksを少し触ったことがあるくらい、
Unityなしのゲームプログラミングは初めてだが2/2までに形にすることを目標にがんばる。

今日が12/6なので2ヶ月ないくらいか。


## 記録

このまま作品として提出したいし、自分の強みは自力で調べて
情報を集めながら身につけつつ、作っていけることかなと思い、
どの時期に何を考えていたか記録をつけることにした。

### 12/6

c++でゲームを作るときの標準構成？みたいなのを調べ、
GLFWでウインドウを出すところまで、やった。
GLFW3.2.1を使っていたが、実行時エラーがでて少しハマった。
3.3にバージョン上げればいいみたいな感じで書いてたのでそうした。

そのあとは、市場調査をした。
githubで適当な検索ワードでシンプルめなゲームのリポジトリを何個かみた。
次は、meshをつくって、それにshaderをあてるmeshの位置が動くところまでを目標にする。
※なんとなく、window部分だけclass分けたり、、みたいなリファクタリングをしたくなるだろうが我慢する。とりあえず書くことを目標に。



### 12/9

インターネットで情報を拾ってシェーダーを使って三角形をつくった。
ほとんどコピペしながら模写した。1ファイルにまとまっているので
ちょっとだけわけたい。移動とか回転ってどうするんだろ...

軽く調べ始めたら、今までの復習になりそう+もう少し踏み込んだ？ことが
超丁寧に書いてあるpdfを発見した。
http://marina.sys.wakayama-u.ac.jp/~tokoi/GLFW.pdf
ので移動中とかに読んでおく。
glewも使ったほうがいいのかな。手元にある本(https://www.borndigital.co.jp/book/2020.html)
もつかってるし。

### 12/13

シェーダーのコンパイルまわりがなんとなく落ち着きそうな雰囲気を
見せてきた。が、今日は時間が限界
3日に1回数時間しか作業できてなくて焦るーー




### 12/12

シェーダーのコンパイルらへんでつまる。
どうやら色んな方法があるみたい、とファイルをわけるのもなかなかうまくいかない

### 12/16

やっとシェーダーのファイルを分けてコンパイルして使うことができた。
Xcodeでfstreamでファイル読めないのに地味に手間取ったりした。
(edit schemeでプロジェクトパス指定してなかったから相対パスで読み込めてなかった)

でもいろんなコード比較しながらコードを読んだので詳細が理解できた、気がする。





