using Microsoft.EntityFrameworkCore;
using OnlineShop.Api.Data;
using OnlineShop.Api.Dto;
using OnlineShop.Api.Entities;
using OnlineShop.Api.Repositories.Contracts;

namespace OnlineShop.Api.Repositories;

public class OrderRepository : IOrderRepository
{
    protected readonly ShopDbContext _context;
    public OrderRepository(ShopDbContext shopOnlineDbContext)
    {
       _context = shopOnlineDbContext;
    }

    public void Add(Order order)
    {
        _context.Orders.Add(order);
    }

    public Order? GetById(int id)
    {
        return _context.Orders.Find(id);
    }

    public void Save()
    {
        _context.SaveChanges();
    }
}