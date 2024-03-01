namespace Application.Dto;

public class MovieUploadDto
{
    public int CountryId { get; set; }

    public int GenreId { get; set; }

    public string Title { get; set; }

    public string Annotation { get; set; }

    public IFormFile Image { get; set; }

    public IFormFile Movie { get; set; }

    public float Rating { get; set; }

    public TimeSpan Length { get; set; }

    public int Year { get; set; }
}
