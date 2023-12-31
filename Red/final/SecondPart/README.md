## Задание по программированию «Поисковая система»

### Вторая часть задачи

В этой части мы смоделируем работу web-сервера, который одновременно  обрабатывает несколько потоков поисковых запросов, а также обновления  базы документов. Ваша реализация будет тестироваться так:

```cpp
void TestSearchServer(vector<pair<istream, ostream*>> streams) {
  // IteratorRange — шаблон из задачи Paginator
  // random_time() — функция, которая возвращает случайный
  // промежуток времени

  LOG_DURATION("Total");
  SearchServer srv(streams.front().first);
  for (auto& [input, output] :
       IteratorRange(begin(streams) + 1, end(streams))) {
    this_thread::sleep_for(random_time());
    if (!output) {
      srv.UpdateDocumentBase(input);
    } else {
      srv.AddQueriesStream(input, *output);
    }
  }
}
```

Как видите, с помощью макроса LOG_DURATION мы замеряем общее время  работы тестирующей функции. Ваша реализация должна работать быстрее, чем простое последовательное применение методов UpdateDocumentBase и  AddQueriesStream.

На практике такой web-сервер бо̀льшую часть времени обрабатывает  поисковые запросы. База документов обновляется не очень часто с  определённой периодичностью, например, один раз в сутки. Обновление базы может занимать значительное время, поэтому сервер не должен прекращать  обработку запросов, пока оно выполняется. Ваше решение второй части  задачи должно это учитывать.

1. Метод AddQueriesStream должен быть готов к тому, что параллельно с ним будет выполняться метод UpdateDocumentBase и наоборот.
2. Метод AddQueriesStream не обязан обрабатывать все запросы с той  версией базы документов, которая была актуальна во время его запуска. То есть, если во время работы метода AddQueriesStream база документов была обновлена, он может использовать новую версию базы для обработки  оставшихся запросов.

**Подсказки для второй части**

[Подсказка_1_2.pdf](https://stepik.org/media/attachments/lesson/285359/Подсказка_1_2.pdf)

[Подсказка_2_2.pdf](https://stepik.org/media/attachments/lesson/285359/Подсказка_2_2.pdf)

[Подсказка_3_2.pdf](https://stepik.org/media/attachments/lesson/285359/Подсказка_3_2.pdf)

[Подсказка_4_2.pdf](https://stepik.org/media/attachments/lesson/285359/Подсказка_4_2.pdf)

### Благодарность

Благодарим [Василия Зяблицева](https://www.coursera.org/user/91db60f0dd0fd4128bd789647136b440) за помощь в усовершенствовании этой задачи.
