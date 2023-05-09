package net;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import java.awt.Color;
import java.awt.Point;
import objects.GraphicObject;
import objects.Image;
import objects.Polygon;
import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;
import retrofit2.Retrofit;
import retrofit2.converter.gson.GsonConverterFactory;
import utils.RuntimeTypeAdapterFactory;

import java.util.List;
import utils.ColorJsonConverter;
import utils.PointJsonConverter;

public class RESTNetworkRepository extends NetworkRepository {

    static final String BASE_URL = "http://localhost:4567/";

    private ObjectServiceAPI api; 
    
    public void start() {
        RuntimeTypeAdapterFactory<GraphicObject> runtimeTypeAdapterFactory
                = RuntimeTypeAdapterFactory
                .of(GraphicObject.class, "type")
                .registerSubtype(Image.class, "image")
                .registerSubtype(Polygon.class, "polygon");
        Gson gson = new GsonBuilder()
                .setLenient()
                .registerTypeAdapterFactory(runtimeTypeAdapterFactory)
                .registerTypeAdapter(Point.class, new PointJsonConverter())
                .registerTypeAdapter(Color.class, new ColorJsonConverter())
                .create();
        Retrofit retrofit = new Retrofit.Builder()
                .baseUrl(BASE_URL)
                .addConverterFactory(GsonConverterFactory.create(gson))
                .build();
        
        api = retrofit.create(ObjectServiceAPI.class);
    }

    public RESTNetworkRepository() {
        start();
    }

    @Override
    public void sendObject(GraphicObject object) {
        api.sendObject(object).enqueue(new Callback<>() {
            @Override
            public void onResponse(Call<Void> call, Response<Void> response) {
                System.out.println("Object sent");
            }

            @Override
            public void onFailure(Call<Void> call, Throwable throwable) {
                System.out.println("Error occurred");
                throwable.printStackTrace();
            }
        });
    }

    @Override
    public void requestObjectByIndex(int index) {
        api.fetchObjectByIndex(index).enqueue(new Callback<>() {
            @Override
            public void onResponse(Call<GraphicObject> call, Response<GraphicObject> response) {
                if (response.body() == null) {
                    System.out.println("Body is empty");
                    return;
                }
                
                listeners.forEach(listener -> listener.onReceiveObject(response.body()));
            }

            @Override
            public void onFailure(Call<GraphicObject> call, Throwable throwable) {
                System.out.println("Error occurred");
                throwable.printStackTrace();
            }
        });
    }

    @Override
    public void requestObjectsList() {
        api.fetchObjects().enqueue(new Callback<>() {
            @Override
            public void onResponse(Call<List<GraphicObject>> call, Response<List<GraphicObject>> response) {
                if (response.body() == null) {
                    System.out.println("Body is empty");
                    return;
                }
                
                listeners.forEach(listener -> listener.onReceiveObjects(response.body()));
            }

            @Override
            public void onFailure(Call<List<GraphicObject>> call, Throwable throwable) {
                System.out.println("Error occurred");
                throwable.printStackTrace();
            }
        });
    }

    @Override
    public void requestObjectsListNames() {
        api.fetchObjectNames().enqueue(new Callback<>() {
            @Override
            public void onResponse(Call<List<String>> call, Response<List<String>> response) {
                if (response.body() == null) {
                    System.out.println("Body is empty");
                    return;
                }
                
                listeners.forEach(listener -> listener.onReceiveObjectNames(response.body()));
            }

            @Override
            public void onFailure(Call<List<String>> call, Throwable throwable) {
                System.out.println("Error occurred");
                throwable.printStackTrace();
            }
        });
    }

    @Override
    public void removeObjectByIndex(int index) {
        api.removeObjectByIndex(index).enqueue(new Callback<>() {
            @Override
            public void onResponse(Call<Void> call, Response<Void> response) {
                System.out.println("Object removed");
            }

            @Override
            public void onFailure(Call<Void> call, Throwable throwable) {
                System.out.println("Error occurred");
                throwable.printStackTrace();
            }
        });
    }
}
