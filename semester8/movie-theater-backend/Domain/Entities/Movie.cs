using System.ComponentModel.DataAnnotations.Schema;

namespace Domain.Entities;

public class Movie
{
    public int Id { get; set; }

    public required int CountryId { get; set; }

    public required int GenreId { get; set; }

    public required string Title { get; set; }

    public required string Annotation { get; set; }

    public required string ImageObjectName { get; set; }

    public required string MovieObjectName { get; set; }

    public required int Year { get; set; }

    public int ScoresSum { get; set; }

    public int ScoresCount { get; set; }

    public required TimeSpan Length { get; set; }

    [ForeignKey("CountryId")]
    public virtual Country Country { get; set; } = null!;

    [ForeignKey("GenreId")]
    public virtual Genre Genre { get; set; } = null!;
}