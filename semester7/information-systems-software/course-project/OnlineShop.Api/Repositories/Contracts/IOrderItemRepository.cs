using OnlineShop.Api.Dto;
using OnlineShop.Api.Entities;

namespace OnlineShop.Api.Repositories.Contracts;

public interface IOrderItemRepository
{

    public void Add(OrderItem item);

    public List<OrderItem> GetByOrderId(int orderId);

    public void Save();
}