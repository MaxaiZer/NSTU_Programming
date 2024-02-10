using System.ComponentModel.DataAnnotations.Schema;

namespace OnlineShop.Api.Entities;

public class PickupPoint
{
    public int Id { get; set; }

    public required string City { get; set; }

    public required string Address { get; set; }
}