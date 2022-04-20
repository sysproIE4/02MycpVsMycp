# mycp と mycp2_1 と mycp2_1024 の性能比較

次の３種類のファイルコピープログラムの性能を比較する．  
mycp ： 高水準I/Oを使用（３年次に作成したもの）  
mycp2_1 ： バッファサイズ1バイトで低水準I/Oを使用  
mycp2_1024 ： バッファサイズ1024バイトで低水準I/Oを使用

1. ３つのプログラムをコンパイルして準備する．

   ```bash
   $ cc -o mycp mycp.c
   ## ここで mycp2.c の BSIZ を 1 に変更する
   $ cc -o mycp2_1 mycp2.c
   ## ここで mycp2.c の BSIZ を 1024 に変更する
   $ cc -o mycp2_1024 mycp2.c
   ```

1. コピー時間測定用のファイルを準備する．  
（実行時間が比較しやすいように，実行するコンピュータに合わせてファイルサイズを調整する）

   ```bash
   $ dd if=/dev/urandom of=aaa bs=1024 count=2560  <-- 2.5MiBのファイルaaaを作る
   2560+0 records in
   2560+0 records out
   2621440 bytes transferred in 0.029957 secs (87506596 bytes/sec)
   $ ls -l aaa
   -rw-r--r--  1 sigemura  staff   2621440 Apr 15 17:35 aaa  <-- できている
   $ /usr/bin/time -p ./mycp2_1024 aaa bbb <-- 時間を計りながら実行する
   real     0.13
   user     0.00
   sys      0.02
   $ /usr/bin/time -p ./mycp2_1024 aaa bbb
   real     0.03
   user     0.00
   sys      0.02
   ## 実行時間は0.03秒だった（１回目の実行結果は使用しない）

   ## real が 0.05 秒程度になるようにファイルサイズを調整する
   $ dd if=/dev/urandom of=aaa bs=1024 count=5120  <-- ファイルサイズを5MiBに変更
   5120+0 records in
   5120+0 records out
   5242880 bytes transferred in 0.047938 secs (109368230 bytes/sec)
   $ /usr/bin/time -p ./mycp2_1024 aaa bbb
   real     0.04                         <-- 0.05秒より少し短いけどOk
   user     0.00
   sys      0.03
   ```

1. 実行時間の測定

   ３つのプログラムについて time コマンドで時間を測定する．  
   測定は３回行い mycp2.c の最後に準備してある表に書き込む．

   ```bash
   $ /usr/bin/time -p ./mycp2_1 aaa bbb
   real    18.09
   user     2.47
   sys     15.55
   $ cmp aaa bbb        <--- コピー結果が正常かチェック
   $
   ```

   mycp2.c の最後に準備してある表に
   実行環境，ファイルサイズ，実行時間を書き加える．

   ```C
   ... プログラム ...
   }

   /* 実行時間のまとめ
   実行したコンピュータ：徳山高専VDI

   実行したコンピュータのOS：Ubuntu Linux

   ファイルサイズ：5MiB    <------ ファイルサイズを追記する
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
