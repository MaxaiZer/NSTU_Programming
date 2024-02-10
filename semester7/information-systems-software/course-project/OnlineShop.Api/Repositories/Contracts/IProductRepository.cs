using OnlineShop.Api.Entities;

namespace OnlineShop.Api.Repositories.Contracts;

public interface IProductRepository
{
    public IEnumerable<Smartphone> GetAll();

    public IEnumerable<Smartphone> Search(string name);

    public Smartphone? GetById(int id);

    public void Add(Smartphone item);

    public void Update(Smartphone item);

    public bool RemoveById(int id);

    public void Save();
}