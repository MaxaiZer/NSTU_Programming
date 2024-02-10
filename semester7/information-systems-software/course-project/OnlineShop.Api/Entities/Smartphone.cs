using System.ComponentModel.DataAnnotations;

namespace OnlineShop.Api.Entities;

public class Smartphone
{
    public int Id { get; set; }

    public required string ImageUrl { get; set; }

    public required string Model { get; set; }

    public required string OS { get; set; }

    public required float Diagonal { get; set; }

    public required int Cores { get; set; }

    public required int RAM { get; set; }

    public required int BatteryCapacity { get; set; }

    public required int ReleaseYear { get; set; }

    public required float DefaultPrice { get; set; }

    public required float CurrentPrice { get; set; }
}