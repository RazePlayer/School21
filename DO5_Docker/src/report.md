## Part 1. Готовый докер

##### Возьми официальный докер-образ с **nginx** и выкачай его при помощи `docker pull`.

![alt text](../misc/images/1.png)

##### Проверь наличие докер-образа через `docker images`.
##### Запусти докер-образ через `docker run -d [image_id|repository]`.
![alt text](../misc/images/2.png)

-d: это флаг, который указывает Docker на запуск контейнера в фоновом режиме (detached mode). Это означает, что контейнер будет работать в фоновом режиме, и командная строка будет освобождена для дальнейшего использования.

##### Проверь, что образ запустился через `docker ps`.
![alt text](../misc/images/3.png)

##### Посмотри информацию о контейнере через `docker inspect [container_id|container_name]`.
![alt text](../misc/images/4.png)
##### По выводу команды определи и помести в отчёт размер контейнера, список замапленных портов и ip контейнера.

![alt text](../misc/images/5.png)

![alt text](../misc/images/6.png)

![alt text](../misc/images/7.png)

##### Останови докер контейнер через `docker stop [container_id|container_name]`.
##### Проверь, что контейнер остановился через `docker ps`.
![alt text](../misc/images/8.png)

##### Запусти докер с портами 80 и 443 в контейнере, замапленными на такие же порты на локальной машине, через команду *run*.
![alt text](../misc/images/9.png)
![alt text](../misc/images/10.png)

##### Проверь, что в браузере по адресу *localhost:80* доступна стартовая страница **nginx**.

![alt text](../misc/images/11.png)

##### Перезапусти докер контейнер через `docker restart [container_id|container_name]`.
![alt text](../misc/images/12.png)
![alt text](../misc/images/13.png)

## Part 2. Операции с контейнером

##### Прочитай конфигурационный файл *nginx.conf* внутри докер контейнера через команду *exec*.
![alt text](../misc/images/14.png)

##### Создай на локальной машине файл *nginx.conf*.
Создала через команду touch

##### Настрой в нем по пути */status* отдачу страницы статуса сервера **nginx**.
![alt text](../misc/images/15.png)

##### Скопируй созданный файл *nginx.conf* внутрь докер-образа через команду `docker cp`.
![alt text](../misc/images/16.png)
##### Перезапусти **nginx** внутри докер-образа через команду *exec*.
![alt text](../misc/images/17.png)
##### Проверь, что по адресу *localhost:80/status* отдается страничка со статусом сервера **nginx**.
![alt text](../misc/images/18.png)
##### Экспортируй контейнер в файл *container.tar* через команду *export*.
![alt text](../misc/images/19.png)
##### Останови контейнер.
![alt text](../misc/images/20.png)
##### Удали образ через `docker rmi [image_id|repository]`, не удаляя перед этим контейнеры.
![alt text](../misc/images/21.png)
##### Удали остановленный контейнер.
![alt text](../misc/images/22.png)
##### Импортируй контейнер обратно через команду *import*.
![alt text](../misc/images/23.png)
##### Запусти импортированный контейнер.
![alt text](../misc/images/24.png)
##### Проверь, что по адресу *localhost:80/status* отдается страничка со статусом сервера **nginx**.
![alt text](../misc/images/25.png)
![alt text](../misc/images/26.png)
## Part 3. Мини веб-сервер

##### Напиши мини-сервер на **C** и **FastCgi**, который будет возвращать простейшую страничку с надписью `Hello World!`.
![alt text](../misc/images/27.png)
![alt text](../misc/images/28.png)
##### Запусти написанный мини-сервер через *spawn-fcgi* на порту 8080.
![alt text](../misc/images/29.png)
##### Напиши свой *nginx.conf*, который будет проксировать все запросы с 81 порта на *127.0.0.1:8080*.
##### Проверь, что в браузере по *localhost:81* отдается написанная тобой страничка.
##### Положи файл *nginx.conf* по пути *./nginx/nginx.conf* (это понадобится позже).
![alt text](../misc/images/30.png)
![alt text](../misc/images/31.png)
![alt text](../misc/images/32.png)
![alt text](../misc/images/33.png)
![alt text](../misc/images/34.png)
![alt text](../misc/images/35.png)
## Part 4. Свой докер

#### Напиши свой докер-образ, который:
##### 1) собирает исходники мини сервера на FastCgi из [Части 3](#part-3-мини-веб-сервер);
##### 2) запускает его на 8080 порту;
##### 3) копирует внутрь образа написанный *./nginx/nginx.conf*;
##### 4) запускает **nginx**.
![alt text](../misc/images/36.png)
![alt text](../misc/images/37.png)

##### Собери написанный докер-образ через `docker build` при этом указав имя и тег.
![alt text](../misc/images/38.png)
##### Проверь через `docker images`, что все собралось корректно.
![alt text](../misc/images/39.png)
##### Запусти собранный докер-образ с маппингом 81 порта на 80 на локальной машине и маппингом папки *./nginx* внутрь контейнера по адресу, где лежат конфигурационные файлы **nginx**'а (см. [Часть 2](#part-2-операции-с-контейнером)).
![alt text](../misc/images/40.png)

##### Допиши в *./nginx/nginx.conf* проксирование странички */status*, по которой надо отдавать статус сервера **nginx**.
![alt text](../misc/images/41.png)
![alt text](../misc/images/42.png)
## Part 5. **Dockle**
![alt text](../misc/images/43.png)

##### Просканируй образ из предыдущего задания через `dockle [image_id|repository]`.
##### Исправь образ так, чтобы при проверке через **dockle** не было ошибок и предупреждений.
![alt text](../misc/images/44.png)
![alt text](../misc/images/45.png)

## Part 6. Базовый **Docker Compose**

![alt text](../misc/images/46.png)
##### 1) Подними докер-контейнер из [Части 5](#part-5-инструмент-dockle) _(он должен работать в локальной сети, т. е. не нужно использовать инструкцию **EXPOSE** и мапить порты на локальную машину)_.
##### 2) Подними докер-контейнер с **nginx**, который будет проксировать все запросы с 8080 порта на 81 порт первого контейнера.
##### Замапь 8080 порт второго контейнера на 80 порт локальной машины.
![alt text](../misc/images/42.png)
##### Останови все запущенные контейнеры.
![alt text](../misc/images/46.png)
##### Собери и запусти проект с помощью команд `docker-compose build` и `docker-compose up`.
![alt text](../misc/images/47.png)
##### Проверь, что в браузере по *localhost:80* отдается написанная тобой страничка, как и ранее.
![alt text](../misc/images/48.png)