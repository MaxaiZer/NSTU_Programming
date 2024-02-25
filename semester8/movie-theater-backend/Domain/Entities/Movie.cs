namespace Domain.Entities;

public class Movie
{
    public int Id { get; set; }

    public required string Title { get; set; }

    public required string Annotation { get; set; }

    public required string PosterPath { get; set; }

    public required string MoviePath { get; set; }

    public int ScoresSum { get; set; }

    public int ScoresCount { get; set; }
}