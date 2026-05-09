Mutex          |  Ne Korur                | neden
fork[i]        |çatal(kaynak)             | aynı anda iki kişi alması
print_lock     |stdout (printf)           | Çıktı karışmasın
death_lock     | someone_died / zamanlar  | Tutarlı okuma-yazma

join olmadığı zaman thread dah işini yapmadan ölür.
jpin varsa:
1- main bekler
2-t1 işini tamamlar
3-program düzgün kapanır.
 