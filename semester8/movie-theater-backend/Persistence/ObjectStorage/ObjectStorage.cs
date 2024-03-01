using System.Net.Http.Headers;
using Microsoft.AspNetCore.Mvc;
using Minio;
using Minio.DataModel.Args;

namespace Application.ObjectStorage;

public class ObjectStorage: IObjectStorage
{
    protected readonly IMinioClient _minioClient;
    protected readonly string _movieBucket = "movies";
    protected readonly string _imageBucket = "images";

    public ObjectStorage(IMinioClient minioClient)
    {
        _minioClient = minioClient;
    }

    public async Task PutObjectAsync(IFormFile file, ObjectType type, string name)
    {
        string bucket = GetBucketNameByObjectType(type);

        using (var stream = file.OpenReadStream())
        {
            PutObjectArgs args = new PutObjectArgs()
                .WithBucket(bucket)
                .WithStreamData(stream)
                .WithObject(name)
                .WithObjectSize(file.Length)
                .WithContentType(file.ContentType);

            if (!await _minioClient.BucketExistsAsync(new BucketExistsArgs().WithBucket(bucket)))
            {
                await _minioClient.MakeBucketAsync(new MakeBucketArgs().WithBucket(bucket));
            }
            await _minioClient.PutObjectAsync(args);
        }
    }

    public async Task<string> PresignedGetObjectAsync(ObjectType type, string name, int expireTime)
    {
        /*string bucket = GetBucketNameByObjectType(type);

        PresignedGetObjectArgs args = new PresignedGetObjectArgs()
            .WithBucket(bucket)
            .WithObject(name)
            .WithExpiry(expireTime);

        return await _minioClient.PresignedGetObjectAsync(args);
        */

        // костыль :)
        return "http://46.19.66.180:9000/" + GetBucketNameByObjectType(type) + "/" + name;
    }

    protected string GetBucketNameByObjectType(ObjectType type)
    {
        return type switch
        {
            ObjectType.Image => _imageBucket,
            ObjectType.Movie => _movieBucket,
            _ => throw new Exception("Object type is unknown"),
        };
    }
}