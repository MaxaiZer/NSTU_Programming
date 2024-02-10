using OnlineShop.Api.Entities;

namespace OnlineShop.Api.Repositories.Contracts;

public interface IPickupPointRepository
{
    public IEnumerable<PickupPoint> GetAll();

    public PickupPoint? GetById(int id);
}