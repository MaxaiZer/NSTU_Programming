namespace OnlineShop.Api.Dto;

public class OrderDto
{
    public required int PickupPointId { get; set; }

    public required string Phone { get; set;}

    public required List<CartItemDto> CartItems { get; set; }
}