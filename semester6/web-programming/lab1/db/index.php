<!DOCTYPE html>
<html>
<style>
    @import url("../../css/styles.css");
</style>

<head>
    <p>Отзыв об обучении</p>
</head>

<body>
    <menu type="toolbar">
    <li>
        <menu label="Файл">
        <button type="button">Новый...</button>
        <button type="button">Открыть...</button>
        <button type="button">Сохранить</button>
        </menu>
    </li>
    <li>
        <menu label="Правка">
        <button type="button">Копировать</button>
        <button type="button">Вырезать</button>
        <button type="button">Вставить</button>
        </menu>
        </li>
    </menu>
    <menu type="context" id="popup-menu">
        <menu_item>Вывести данные</menu_item>
        <menu_item>Добавить данные</menu_item>
        <menu_item>Изменить данные</menu_item>
        <menu_item>Удалить данные</menu_item>
    </menu>
    <form action="db_request_handler.php" METHOD=POST>
        <label>ДБ</label>
        <p><input type="text" name="name" value=""><Br>
        </p>
        <p><input type="submit" value="Отправить"></p>
    </form>
</body>

</html>