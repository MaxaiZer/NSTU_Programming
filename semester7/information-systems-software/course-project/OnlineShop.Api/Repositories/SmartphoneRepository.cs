using Microsoft.EntityFrameworkCore;
using OnlineShop.Api.Data;
using OnlineShop.Api.Entities;
using OnlineShop.Api.Repositories.Contracts;

namespace OnlineShop.Api.Repositories;

public class SmartphoneRepository : IProductRepository
{
    protected readonly ShopDbContext _context;
    public SmartphoneRepository(ShopDbContext context)
    {
        _context = context;
    }
    
    public void Add(Smartphone item)
    {
        _context.Smartphones.Add(item);       
    }

    public IEnumerable<Smartphone> GetAll()
    {
        return _context.Smartphones.ToList();
    }

    public IEnumerable<Smartphone> Search(string name)
    {
        name = name.ToLower();
        return _context.Smartphones.Where(item => item.Model.ToLower().Contains(name));
    }

    public Smartphone? GetById(int id)
    {
        return _context.Smartphones.Find(id);
    }
    public bool RemoveById(int id)
    {
        var item = _context.Smartphones.Find(id);
        if (item == null)
            return false;

        _context.Set<Smartphone>().Remove(item);
        return true;
    }

    public void Update(Smartphone item)
    {
        _context.Smartphones.Update(item);
    }

    public void Save()
    {
        _context.SaveChanges();
    }
}