# command-search
Windowsのコマンドプロンプトにコマンドラインからweb検索できるような機能を追加させるツールです。

# 実行環境
Windows cmd.exe  
Windows APIの機能を一部利用しているため、Windowsでないと正しく実行されません。  

# インストール方法
releaseよりダウンロードしたcmds.zipを展開した後、本体のcmds.exeをインストールしたい場所に移動させ、そのディレクトリパスをWindowsの設定の「環境変数」よりPathを通すことでコマンドラインで実行できるようになります。  
Windowsキーを押した後に[path]と打ち込むと設定画面を簡単に表示させることができます。  

# 使用方法
[cmds]と入力した後、コマンドを打つことで操作します。

    cmds [command] [検索ワード]

設定したコマンドを使用して[検索ワード]をweb検索します。


    cmds -add [command] [URL]

-addコマンドを使用することで、[command]と[URL]を紐づけし、[command]をコマンドとして追加します。  
[URL]はwebURLの「○○.com/search?q=」などのような、検索キーワードの部分を除外したURLを入力する必要があることに注意してください。


    cmds -del [command]

登録した[command]を削除します。紐づけされていた[URL]も共に削除されます。


    cmds -list

今まで登録した[command]と[URL]の一覧を表示します。
