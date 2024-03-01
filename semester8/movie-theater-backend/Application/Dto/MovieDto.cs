namespace Application.Dto;

public class MovieDto
{
    public required int Id { get; set; }

    public required string Title { get; set; }

    public required string Annotation { get; set; }

    public required float Rating { get; set; }

    public required TimeSpan Length { get; set; }

    public required string Country { get; set; }

    public required string Genre { get; set; }

    public required int Year { get; set; }

    public required string ImageUrl { get; set; }

    public required string MovieUrl { get; set; }
}
