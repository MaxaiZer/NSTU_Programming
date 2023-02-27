jQuery(document).ready(function(){
   
        jQuery('[name=brand_id]').change(function(){
     
            const value=$("select[name=brand_id] option:selected").val();

            $('select[name=model_id] option').remove();

          //  if(!value) 
            //    $('select[name=model]').append('<option value='+0+'>Выберите марку</option>');

            $.get("get_models.php?brand_id="+value, function(data) {

                const ids = data.getElementsByTagName('id');
                const models = data.getElementsByTagName('name');
                
                for (var i = 0; i < ids.length; i++) {
                    const id = ids.item(i).firstChild.data;
                    const data = models.item(i).firstChild.data;
                    $('select[name=model_id]').append('<option value='+id+'>'+data+'</option>');
                }
            });
        });
    }
);