#!/bin/bash

TOKEN="7983725316:AAFyUM90MWOxwdUrNrwpt1b97-o2ZL1PsS0"
CHAT_ID="415757388"
STATUS=$1
if [ "$STATUS" == "SUCCESS" ]; then
    MESSAGE="🎉 Успешное завершение этапов CI/CD! Все шаги прошли без ошибок."
elif [ "$STATUS" == "FAILURE" ]; then
    MESSAGE="⚠️ Ошибка при выполнении пайплайна CI/CD! Проверьте логи для деталей."
else
    MESSAGE="Неизвестный статус выполнения: $STATUS"
fi
curl -s -X POST "https://api.telegram.org/bot$TOKEN/sendMessage" \
    -d chat_id="$CHAT_ID" \
    -d text="$MESSAGE" \
    -d parse_mode="HTML"