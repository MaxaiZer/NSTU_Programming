using OnlineShop.Api.Entities;

namespace OnlineShop.Api.Dto;

public class OrderDetailDto
{
    public int Id { get; set; }

    public required string Phone { get; set; }

    public required PickupPoint PickupPoint { get; set; }

    public required List<string> ItemsNames { get; set; }

    public required List<int> ItemsQuantities { get; set; }

    public required float Total { get; set; }

    public required DateOnly Date { get; set; }
}