using Microsoft.EntityFrameworkCore;
using OnlineShop.Api.Data;
using OnlineShop.Api.Dto;
using OnlineShop.Api.Entities;
using OnlineShop.Api.Repositories.Contracts;

namespace OnlineShop.Api.Repositories;

public class OrderItemRepository : IOrderItemRepository
{
    protected readonly ShopDbContext _context;
    public OrderItemRepository(ShopDbContext shopOnlineDbContext)
    {
       _context = shopOnlineDbContext;
    }

    public void Add(OrderItem item)
    {
        _context.Add(item);
    }

    public List<OrderItem> GetByOrderId(int orderId)
    {
        return _context.OrderItems.Where(item => item.OrderId == orderId).ToList();
    }

    public void Save()
    {
        _context.SaveChanges();
    }
}