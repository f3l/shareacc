# shareacc
Share your accounts with your friends over a webpanel

## Introduction
1. Add the files in htdocs/ and cgi-bin/ to the related folders of your http server.
2. Compile the files in cgi-bin/ with make or your favourite compiler
3. Set all required rights to shareacc and switch
4. Copy the shareacc.cfg.example to shareacc.cfg and change the values as needed
5. Have fun ;)

## shareacc.cfg
The shareacc.cfg is a ini config file. (Yeah, I know, it's not for temporary things... I will fix this in a following version.)

  * You have to set at least two sections, the [main] and the [1] section.
  * When you want to add more than one account, you must entitle very section with [(previous section)+1]

```ini
[main]
title=Foo Bar

[1] 
type=example.com
owner=Li Ziege
user=li.ziege
password=foobar123
expired=No
used=No
last_modified=0

[2]
...
```
