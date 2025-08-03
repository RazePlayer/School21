## Part 1. Installation of the OS

* command cat /etc/issue.

    ![alt text](../misc/images/1.png)

## Part 2. Creating a user

* Создание нового пользователя и добавление его в группу adm

    sudo useradd new_kam

    sudo usermod -a -G adm new_kam

    cat /etc/passwd

    ![alt text](../misc/images/2.png)

## Part 3. Setting up the OS network
* Изменение названия машины

    ![alt text](../misc/images/3_1.png)

* Установка временной зоны

    ![alt text](../misc/images/3_2.png)

* Вывод названия сетевых интерфейсов

    ![alt text](../misc/images/3_3.png)

    Интерфейс lo виртуальный интерфейс всегда присутствующий на linux. Используется для отладки сетевых программ и запуска серверных приложений на локальной машине. 
    У него всегда адрес 127.0.0.1

* Получаем новый IP от DHCP

    ![alt text](../misc/images/3_4.png)

    DHCP - Dynamic Host Configuration Protocol

* Внешний и внутренний IP

    ![alt text](../misc/images/3_5.png)

* Задаем статичный IP в конфигурационном файле
    sudo vim /etc/netplan/00-installer-config.yaml

    ![alt text](../misc/images/3_6.png)

* Применяем изменения: sudo netplan apply

* Перезагружаем: reboot

    Проверяем, что у нас теперь статичный IP

    ![alt text](../misc/images/3_7.png)

    Пингуем удаленные хосты 1.1.1.1 и ya.ru

    ![alt text](../misc/images/3_8.png)

    ![alt text](../misc/images/3_9.png)

## Part 4. OS Update
* Установка обновлений

   sudo apt upgrade

    ![alt text](../misc/images/4.png)

## Part 5. Using the sudo command
*  Наделение правами другого пользователя и изменение названия машина с правами root от другого пользователя:

    ![alt text](../misc/images/5.png)

    С помощью sudo (substitute user and do, подменить пользователя и выполнить) пользователь может выполнить привелигиированные команды без необходимости быть суперпользователем root.

## Part 6. Installing and configuring the time service
* Установка и настройка службы времени

    sudo apt install systemd-timesyncd

    sudo systemctl enable systemd-timesyncd

    sudo systemctl start systemd-timesyncd

    ![alt text](../misc/images/6.png)

## Part 7. Installing and using text editors
* Сохранение

    vim - :wq and Enter

    ![alt text](../misc/images/7_1.png)

    nano - Ctrl + O and Enter

    ![alt text](../misc/images/7_2.png)

    joe - Ctrl + K and X

    ![alt text](../misc/images/7_3.png)

* Выход без сохранения

    vim - :q!
    
    ![alt text](../misc/images/7_4.png)

    nano - Ctrl + X and NO

    ![alt text](../misc/images/7_5.png)

    joe - Ctrl + C and YES

    ![alt text](../misc/images/7_6.png)

* Поиск по файлу

    vim : /idellbel

    ![alt text](../misc/images/7_7.png)

    nano - Ctrl + W and idellbel

    ![alt text](../misc/images/7_8.png)

    joe - Ctrl + K and F and idellbel

    ![alt text](../misc/images/7_9.png)

    vim - :%s/idellbel/karina/g

    ![alt text](../misc/images/7_10.png)

    nano - Ctrl + \ 

    ![alt text](../misc/images/7_11.png)

    joe - Ctrl + K and F and R(eplace)
    
    ![alt text](../misc/images/7_12.png)

## Part 8. Installing and basic setup of the SSHD service
* Установка службы SSHd 
    sudo apt install openssh-server

    ![alt text](../misc/images/8_1.png)

* Добавила автостарт службы при загрузке системы 
    systemctl status sshd

    ![alt text](../misc/images/8_2.png)

* Перенастроила службу SSHd на порт 2022
    sudo vim /etc/ssh/sshd_config

    ![alt text](../misc/images/8_3.png)

* Наличие процесса sshd

    ![alt text](../misc/images/8_4.png)

    ps -C sshd

    ps - команда для того чтобы посмотреть процессы

    -С - флаг позволяет выбрать процесс по имени

* reboot

* netstat -tan

    ![alt text](../misc/images/8_5.png)
    
    Ключи:
    
    -t Отображает TCP подключения

    -a Отображает все активные TCP-подключения и порты TCP и UDP, на которых    компьютер прослушивает

    -n Отображает активные TCP-подключения, однако адреса и номера портов выражаются числовым образом и не предпринимается никаких попыток определения имен
    
* Столбцы
    Proto - протокол (tcp, udp, raw), используемый сокетом

    Recv-Q - счётчик байт не скопированных программой пользователя из этого сокета
    
    Send-Q - счётчик байтов, не подтверждённых удалённым узлом

    Local Address - адрес и номер порта локального конца сокета

    Foreign Address - адрес и номер порта удалённого конца сокета

    State - состояние сокета

    LISTEN - cокет ожидает входящих подключений

    IP-адрес 0.0.0.0 — это немаршрутизируемый адрес IPv4, который можно использовать в разных целях, в основном, в качестве адреса по умолчанию или адреса-заполнителя. Несмотря на то, что адрес 0.0.0.0 может использоваться в компьютерных сетях, он не является адресом какого-либо устройства.

## Part 9. Installing and using the top, htop utilities
* top:

    uptime 13 min

    1 user

    load average: 0.00, 0.08, 0.17

    Tasks: 99 total

    %Cpu(s): 0.7 us, 1.0 sy, 0.0 ni, 98.3 id, 0.0 wa, 0.0 hi, 0.0 si, 0.0 st

    Mib Mem: 1968.2 total, 1605.8 free, 132.0 used, 230.5 buff/cache

    539

    1

    ![alt text](../misc/images/9_1.png)


* htop

    Сортировка по PID

    ![alt text](../misc/images/9_2.png)

    Сортировка по CPU

    ![alt text](../misc/images/9_3.png)

    Сортировка по MEM

    ![alt text](../misc/images/9_4.png)

    Сортировка по TIME

    ![alt text](../misc/images/9_5.png)

    Фильтр sshd

    ![alt text](../misc/images/9_6.png)

    Поиск syslog

    ![alt text](../misc/images/9_7.png)

    Добавление hostname, clock, uptime

    ![alt text](../misc/images/9_8.png)

## Part 10. Using the fdisk utility
* Disk /dev/sda: 50 GiB, 53697091200 bytes, 104857600 sectors, 2G

    ![alt text](../misc/images/10_1.png)

    ![alt text](../misc/images/10_2.png)

## Part 11. Using the df utility
* df

    ![alt text](../misc/images/11_1.png)

* df для корневого раздела

    ![alt text](../misc/images/11_1-1.png)

    размер раздела 24050032
    размер занятого пространства 4763856
    размер свободного пространства 18039152
    процент использования 35

* Единица измерения в выводе - килобайты

* df -Th

    ![alt text](../misc/images/11_2.png)

* df -Th для корневого раздела

    ![alt text](../misc/images/11_2-1.png)

    размер раздела 23
    размер занятого пространства 4.6
    размер свободного пространства 18
    процент использования 21

* Tип файловой системы для раздела - ext4

## Part 12. Using the du utility

* du

    ![alt text](../misc/images/12_1.png)

* du -hs /home

    ![alt text](../misc/images/12_2.png)

* sudo du -hs /var 

    ![alt text](../misc/images/12_3.png)

* sudo du -hs /var/log

    ![alt text](../misc/images/12_4.png)

* sudo -h /var/log/*

    ![alt text](../misc/images/12_5.png)

## Part 13. Installing and using the ncdu utility

* sudo apt install ncdu

* ncdu /home

    ![alt text](../misc/images/13_1.png)

* ncdu /var

    ![alt text](../misc/images/13_2.png)

* ncdu /var/log

    ![alt text](../misc/images/13_3.png)

## Part 14. Working with system logs

* vim /var/log/dmesg

    ![alt text](../misc/images/14_1.png)

* vim /var/log/syslog

    ![alt text](../misc/images/14_2.png)

* vim /var/log/auth.log

    ![alt text](../misc/images/14_3.png)

* Время последнего входа: Jun 30, 14:35:03, user admin, method sudo

* Restart sshd: sudo systemctl restart ssh.service
                cat /var/log/syslog | grep ssh

    ![alt text](../misc/images/14_4.png)

## Part 15. Using the CRON job scheduler

* crontab -e
*/2 * * * * uptime

    ![alt text](../misc/images/15_1.png)

* syslog, uptime

    ![alt text](../misc/images/15_2.png)

* список текущих заданий для CRON
    
    ![alt text](../misc/images/15_3.png)

* Удалила все задания из планировщика задач

    ![alt text](../misc/images/15_4.png)

It's all!