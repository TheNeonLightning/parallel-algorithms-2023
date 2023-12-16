Практическое задание #2.

Нужно реализовать параллельный bfs (возьмите алгос с пары, кого не было, спросите конспект с товарищей или же в крайнем
случае у меня спросите). От Вас требуется написать последовательную версию алгоритма (seq) и параллельную версию (par).
Протестировать надо на кубическом графе со стороной 500 и источником в (0, 0, 0). (Усреднить по 5 запускам)
Сравнить время работы par на 4 процессах и seq на одном процессе - у Вас должно быть раза в 3 быстрее.  
(Если будет медленнее, то выставление баллов оставляется на моё усмотрение.) Учтите, что Ваш bfs должен работать на 
любом графе, если Вам дан его список смежности.

Нужен код на гитхабе, видимо, ссылка на него и результаты запусков. Код, который запускает, тоже должен лежать в репо.

Присылать письмо на почту с темой "CW2. <ФИО>".

1. 
Test params: side = 50; runs = 1; checkCorrectness = 0
num vertices = 125000
num edges    = 735000
max degree   = 6
time_seq = 3422ms; time_par = 7567ms; seq/par coef = 0.452227;

2.
Test params: side = 100; runs = 1; checkCorrectness = 0
num vertices = 1000000
num edges    = 5940000
max degree   = 6
time_seq = 41500ms; time_par = 38090ms; seq/par coef = 1.08952;

3.
Test params: side = 200; runs = 1; checkCorrectness = 0
num vertices = 8000000
num edges    = 47760000
max degree   = 6
time_seq = 1.07805e+06ms; time_par = 343883ms; seq/par coef = 3.13493;

4.
Test params: side = 500; runs = 5; checkCorrectness = 0
num vertices = 125000000
num edges    = 748500000
max degree   = 6
time_seq = 2.71801e+07ms; time_par = 7.7991e+06ms; seq/par coef = 3.48503;
time_seq = 2.79558e+07ms; time_par = 8.07206e+06ms; seq/par coef = 3.46328;
time_seq = 2.81024e+07ms; time_par = 8.26218e+06ms; seq/par coef = 3.40134;
time_seq = 2.70089e+07ms; time_par = 8.34547e+06ms; seq/par coef = 3.23635;
time_seq = 2.73822e+07ms; time_par = 8.42975e+06ms; seq/par coef = 3.24829;

| № | time_seq       | time_par       | seq/par coef |
|---|----------------|----------------|--------------|
| 1 | 2.71801e+07ms  | 7.7991e+06ms   | 3.48503      |
| 2 | 2.79558e+07ms  | 8.07206e+06ms  | 3.46328      |
| 3 | 2.81024e+07ms  | 8.26218e+06ms  | 3.40134      |
| 4 | 2.70089e+07ms  | 8.34547e+06ms  | 3.23635      |
| 5 | 2.73822e+07ms  | 8.42975e+06ms  | 3.24829      |

