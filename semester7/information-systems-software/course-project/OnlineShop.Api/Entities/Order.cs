using System.ComponentModel.DataAnnotations.Schema;

namespace OnlineShop.Api.Entities;

public class Order
{
    public int Id { get; set; }

    public required int PickupPointId { get; set; }

    public required string Phone { get; set; }

    public required float Total { get; set; }

    public required DateOnly Date { get; set; }
}