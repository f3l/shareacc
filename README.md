# shareacc
Share your accounts with your friends over a webpanel

## Introduction
1. Add the files in htdocs/ and cgi-bin/ to the related folders of your http server.
3. Set all required rights to files in cgi-bin folder
4. Copy the accounts.yaml.example to accounts.yaml and change the values as needed
5. Have fun ;)

## accounts.yaml
The accounts.yaml is a YAML config file.

  * When you want to add more than one account, you must entitle very section with [(previous section)+1]

```yaml
-
 num: 1
 type: example.com
 owner: Li Ziege
 user: li.ziege
 pass: foobar123

-
...
```
