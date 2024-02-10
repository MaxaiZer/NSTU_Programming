using OnlineShop.Api.Entities;

namespace OnlineShop.Api.Repositories.Contracts;

public interface IOrderRepository
{

    public void Add(Order order);

    public Order? GetById(int id);

    public void Save();
}