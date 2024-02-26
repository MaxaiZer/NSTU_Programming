namespace Domain.Entities;

public class Movie
{
    public int Id { get; set; }

    public required string Title { get; set; }

    public required string Annotation { get; set; }

    public required string PosterObjectName { get; set; }

    public required string MovieObjectName { get; set; }

    public int ScoresSum { get; set; }

    public int ScoresCount { get; set; }

    public required TimeSpan Length { get; set; }
}