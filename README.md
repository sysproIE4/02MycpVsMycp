# mycp と mycp2_1 と mycp2_1024 の性能比較

次の３種類のファイルコピープログラムの性能を比較する．<br>
mycp ： 高水準I/Oを使用（３年次に作成したもの）<br>
mycp2_1 ： バッファサイズ1バイトで低水準I/Oを使用<br>
mycp2_1024 ： バッファサイズ1024バイトで低水準I/Oを使用

1. ３つのプログラムをコンパイルして準備する．

  ```
  $ cc -o mycp mycp.c
  ここで mycp2.c の BSIZ を 1 に変更する
  $ cc -o mycp2_1 mycp2.c
  ここで mycp2.c の BSIZ を 1024 に変更する
  $ cc -o mycp2_1024 mycp2.c
  ```

2. コピー時間測定用の2.5MiBのファイルを準備する．
（ファイルサイズは実行するコンピュータの性能により，
実行時間が比較しやすいように調整すること）

  ```
  $ dd if=/dev/urandom of=aaa bs=1024 count=2560  <-- 2.5MiBのファイルaaaを作る
  2560+0 records in
  2560+0 records out
  2621440 bytes transferred in 0.060575 secs (43275933 bytes/sec)
  $ ls -l aaa
  -rw-r--r--  1 sigemura  staff   2621440 Apr 15 17:35 aaa  <-- できている
  $
  ```

3. 実行時間の測定

  ３つのプログラムについて time コマンドで時間を測定する．<br>
  測定は３回行い mycp2.c の最後に準備してある表に書き込む．

  ```
  $ rm bbb               <--- 念のため bbb を消す
  rm: bbb: No such file or directory
  $ /usr/bin/time -p ./mycp2_1 aaa bbb
  real        16.62
  user         2.02
  sys         14.17
  $ cmp aaa bbb        <--- コピー結果が正常かチェック
  $
  ```

  mycp2.c の最後に準備してある表に結果を書き加える．

  ```
  ... プログラム ...
  }

  /* 実行時間のまとめ
  -------------------------------------
  mycpの実行時間（単位は秒）
  　　　1回目   2回目   3回目   平均
  real
  user
  sys
  -------------------------------------
  mycp2_1の実行時間（単位は秒）
  　　　1回目   2回目   3回目   平均
  real
  user
  sys
  -------------------------------------
  mycp2_1024の実行時間（単位は秒）
  　　　1回目   2回目   3回目   平均
  real
  user
  sys
  -------------------------------------
  感想・考察：

  */
  ```
