# Mini-Shell
The first group project at 42Berlin, my teammate <a href="https://github.com/zaperfish">Zaperfish</a>.  
The subject requires you to create your own representation of a <a href="https://en.wikipedia.org/wiki/Unix_shell">shell</a>.  
While testing, for the most part, we based it on <a href="https://en.wikipedia.org/wiki/Bash_(Unix_shell)">bash</a>.  

This one was one of the most challenging projects through-out my curriculum, mostly because of the many edge-cases this program presented.

# Description
<sub>the subject is included in <i>./en.subject.pdf</i></sub>
<h3>Introduction</h3>
<p>The existence of shells is linked to the very existence of <b>IT</b>.</p>
<p>At the time, all developers agreed that <i>communicating with a computer using aligned
1/0 switches was seriously irritating</i>.</p>
<p>It was only logical that they came up with the idea of creating a software to communicate with a computer using interactive lines of commands in a language somewhat
close to the human language.</p>
<p>Thanks to <b>Minishell</b>, you’ll be able to travel through time and come back to problems
people faced when Windows didn’t exist.</p>

# Install and Run

```bash
git clone https://github.com/VulpesDev/Mini-shell.git ~/minishellVulpes && cd ~/minishellVulpes && make && ./minishell
```

# Usage

Upon running the executable you will be prompted to
```bash
DEATH....>
```
Congratulations, you are now using our shell.
From here on you can play around with it and use it as your system's default shell (I highly recommend against it... ha ha ha)

<h3>Core features<sub>(which are probably worth mentioning)</sub></h3>
<ul>
  <li>Working history <sub>(whenever you type something in the prompt <i>(and press enter)</i>, you can turn back time <i>(up arrow)</i> and get it back in the promt, how cool...)</sub></li>
  <li>Search and launch the right executable <sub><i>(based on the <b>PATH</b> variable or using a relative or an absolute path)</i></sub></li>
  
  ```bash
  DEATH....>ls
  DEATH....>/usr/bin/ls
  ```
  <li>Handle unclosed quotes and dquotes</li>
  <li>Handle <i>'</i><sub>(single quote)</sub> which should prevent the shell from interpreting the meta-characters in the quoted sequence</li>

  ```bash
echo 'hello this pipe should just print as a pipe | as well as all those symbols <>()""(")""$USER$$$$$$$PATH'
  ```
  
  <li>Handle <i>"</i><sub>(double quotes)</sub> which should prevent the shell from interpreting the meta-characters in the quoted sequence except for <i>$</i><sub>(dollar sign)</sub></li>
    
  ```bash
echo "hello this pipe should just print as a pipe | as well as all those symbols <>()''''''(')'' but replace this $USER with the actual user"
  ```

  <li>Implement <b>redirections</b>:
    <ul>
      <li> <i><</i> should redirect input.</li>
      <li> <i>></i> should redirect output.</li>
      <li> <i><<</i> should be given a delimiter, then read the input until a line containing the
delimiter is seen.</li>
      <li> <i><</i> should redirect output in append mode.</li>
    </ul>

```bash
<input.txt wc -l >output.txt
```
<sub>(this requires an existing file <i>input.txt</i>) should create/edit a file <i>output.txt</i> changing its contents to the number of lines in <i>input.txt</i></sub>
<li>Implement <b>pipes</b><sub>(| character)</sub>. The output of each command in the pipeline is
connected to the input of the next command via a pipe.
  <sub>(I hope you still have the <i>input.txt</i>)</sub>

  ```bash
  cat input.txt | wc -l | cat -e
  ```
<li>Handle <b>environment variables</b><sub>($ followed by a sequence of characters)</sub> which should expand to their values.
  
  ```bash
  echo $PATH
  ```

  ```bash
  env
  ```
<sub>(to show the environment variables)</sub>

<li>Handle $? which should expand to the exit status of the most recently executed
foreground pipeline.</li>

```bash
  echo $?
```

<li>Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.</li>
<li>Implement the following <b>builtins</b>:
  <ul>
<li>echo with option -n</li>
<li><i>cd</i> with only a relative or absolute path</li>
<li> <i>pwd</i> with no options</li>
<li> <i>export</i> with no options</li>
<li> <i>unset</i> with no options</li>
<li> <i>env</i> with no options or arguments</li>
<li> <i>exit</i> with no options</li>
  </ul>
<li><i>&&</i> and <i>||</i> and parenthesis for priorities.</li>
<li>Wildcards <i>*</i> should work for the current working directory.</li>
</ul>
<h3>Now get wild</h3>
You can now let your imagination out and do crazy commands like

```bash
  yes | head -10 && (eewqr wrqwr || echo t) && (echo pow && (echo 2 && echo 3) || edwadw) > outfile.txt
```
