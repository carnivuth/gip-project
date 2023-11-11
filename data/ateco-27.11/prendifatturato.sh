#!/bin/bash
for file in *.html; do 
cat $file | pup -i 4 'td'  | grep -v '<a' | grep -v '</' | grep -v '        ' | grep -v '<td' >> fatturatiaziende.txt
cat $file | pup -i 4 'td'  | pup -i 4 '.dark-blue' | grep '    ' >> nomiaziende.txt
done
