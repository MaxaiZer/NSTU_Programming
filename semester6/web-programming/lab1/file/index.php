<!DOCTYPE html>
<html>
<style>
    @import url("../../css/styles.css");
</style>

<body>
    <div style="text-align:center; margin-top: 10%">
    <p>Запись в файл</p>
    <form action="write_to_file.php" METHOD=POST>
        <p><input type="text" name="name" value="" placeholder="Имя"></p>
        <p><textarea name="sites" value="" placeholder="Сайты для управления"></textarea></p>
        <p><button style="padding: 5px 5px;" type="submit">Отправить</button></p>
    </form> 

    <a href="../index.html"><h1>Назад</h1></a>
    </div>
</body>

</html>