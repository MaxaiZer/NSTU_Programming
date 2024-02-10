using Microsoft.EntityFrameworkCore;
using OnlineShop.Api.Data;
using OnlineShop.Api.Dto;
using OnlineShop.Api.Entities;
using OnlineShop.Api.Repositories.Contracts;

namespace OnlineShop.Api.Repositories;

public class PickupPointRepository : IPickupPointRepository
{
    protected readonly ShopDbContext _context;
    public PickupPointRepository(ShopDbContext shopOnlineDbContext)
    {
       _context = shopOnlineDbContext;
    }

    public IEnumerable<PickupPoint> GetAll()
    {
        return _context.PickupPoints.ToList();
    }

    public PickupPoint? GetById(int id)
    {
        return _context.PickupPoints.Find(id);
    }
}