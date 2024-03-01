namespace Application.ObjectStorage;

public interface IObjectStorage
{
    public Task PutObjectAsync(IFormFile file, ObjectType type, string name);

    public Task<string> PresignedGetObjectAsync(ObjectType type, string name, int expireTime);
}