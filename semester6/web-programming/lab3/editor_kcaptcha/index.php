<!DOCTYPE html>
<html>
<style>
    @import url("../../css/styles.css");
</style>

<head>
    <script src="ckeditor5/ckeditor.js"></script>
</head>

<body>
    <h1>CKeditor</h1>
    <form action="write_to_file.php" method="post">

        <textarea name="text" id="editor">
            Текст вводить здесь-)
        </textarea>

        <p></p>
        <img src="kcaptcha/index.php?<?php session_start(); echo session_name()?>=<?php echo session_id()?>"></p>
        <input type="text" name="captcha_answer" placeholder="Код подтверждения">
        <p><button style="padding: 5px 5px;" type="submit">Подтвердить</button></p>
    </form>

    <?php
        session_start();
        if(isset($_SESSION["is_right_captcha"]) && 
        !$_SESSION["is_right_captcha"])
            echo "wrong captcha";
    ?>
    
    <script>
        ClassicEditor
            .create( document.querySelector( '#editor' ) )
            .catch( error => {
                console.error( error );
            } );
    </script>

    <script>

        let text = document.querySelector('[role=textbox]').innerText
        var dataArray = new System.Web.Script.Serialization.JavaScriptSerializer().Serialize(Session["text"])
        dataArray["text"] = text;

    </script>

    <a href="../index.html"><h1>Назад</h1></a>

</body>

</html>