# 42_minishell
A small shell like bash.

# Article
ToYeah :
    
[shellの文字列分解と環境変数展開を再実装した](https://qiita.com/ToYeah0102/items/4c980440ed790d110a7f)

[[bash] カレントディレクトリが存在しなくてもcd ./は成功する
](https://qiita.com/ToYeah0102/items/1e81b2c1d5ce40268eed)

nafuka :

[bash再実装の課題振り返り](https://nafuka.hatenablog.com/entry/2021/03/29/194200)

# Usage

```
git clone https://github.com/ToYeah/42_minishell.git && make -C 42_minishell && ./42_minishell/minishell
```

# Tester
https://github.com/nafuka11/42_minishell_tester


# Feature

* Simple command.  
* Relative path command.  
* Absolute path command.  
```
minishell > ls
minishell > /bin/ls
minishell > ./test.sh
```
* Redirection

```
minishell > ls > ls.txt
minishell > ls >> ls.txt
minishell > cat < ls.txt
minishell > cat < ls.txt 1>out.txt 2>error.txt
```
* Pipe
```
minishell > ls | cat
minishell > ls | cat | grep 42
```
* combination
```
minishell > ls | cat > cat.txt
minishell > cat < cat.txt | grep 42 | wc 1> wc.txt
```

# Builtin command

* echo
```
minishell > echo hello
minishell > echo -n hello
```

* cd 
```
minishell > cd ./dir
minishell > cd /bin
```

* pwd
```
minishell > pwd
```

* export
```
minishell > export PATH="/"
```

* unset
```
minishell > unset
```

* env
```
minishell > env
```

* exit

```
minishell > exit
minishell > exit 42
minishell > exit -- 1
```
