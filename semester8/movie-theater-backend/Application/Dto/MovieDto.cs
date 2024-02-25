namespace Application.Dto;

public class MovieDto
{
    public int Id { get; set; }

    public required string Title { get; set; }

    public required string Annotation { get; set; }

    public required string PosterLink { get; set; }

    public required string MovieLink { get; set; }

  //  public TimeSpan Length { get; set; }

  //  public DateOnly ReleaseDate { get; set; }
}
