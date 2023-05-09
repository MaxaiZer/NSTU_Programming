package net;

import retrofit2.Call;
import retrofit2.http.*;

import java.util.List;
import objects.GraphicObject;

public interface ObjectServiceAPI {
    @GET("objects/get")
    Call<List<GraphicObject>> fetchObjects();
    
    @GET("objects/names")
    Call<List<String>> fetchObjectNames();

    @GET("object/get")
    Call<GraphicObject> fetchObjectByIndex(@Query("id") int index);

    @POST("object/add")
    Call<Void> sendObject(@Body GraphicObject object);

    @DELETE("object/remove")
    Call<Void> removeObjectByIndex(@Query("id") int index);
}
