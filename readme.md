c++からPythonのモジュールをCallする実験場

ビルド時のoption
$ gcc -g call_function.c -o call_function -I`python-config --prefix`/Headers -L`python-config --prefix`/lib -lpython2.7

　かなり長い（これでも`python-config --prefix`を使って、パス名の指定を楽している）

実行方法
$ ./a.out py_function multipy

coreがでる。うまくいかない。

PYTHONPATHという環境変数を設定しないと、pythonモジュールを読み込めないという情報があった。（これ重要）
export PYTHONPATH="/Users/hogehoge/ProgWork/C++_Python"

だが、やっぱりうまくいかない
→いや、emacs内のshellではダメだったが、通常のコンソールではこれでうまくいく。
 実行したら、py_function.pycができていた。

次に引数をpythonモジュールに渡す（call_function1.c py_function1.py）
ビルド時にワーニングがでた。

$ ./call_function1 py_function1 multiply 6 7
The result of  6  x  7  =  42
Return of call : 42

うまくいった。

次にpythonのclassをcallするサンプルを試す。

py_class.pyを作成。call_class.cを作成。
最初はどうしてもうまくいかない。デバッガで調べると、相変わらずPyModuleの読み込みで失敗している。
改めてpythonのサンプルコードを見ると、インデントがおかしい。（pythonはインデントが重要）
そこを直したら、うまくいった。

単純にクラスをcall

$ ./call_class py_class Multiply multiply
The result of 6 x 5 : 30
Return of call : 30

引数付きのメソッドをコール

$ ./call_class py_class Multiply multiply2 8 9
The result of 8 x 9 : 72
Return of call : 72

