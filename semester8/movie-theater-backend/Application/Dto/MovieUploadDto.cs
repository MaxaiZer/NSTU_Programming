namespace Application.Dto;

public class MovieUploadDto
{
    public int UserId { get; set; }

    public string Title { get; set; }

    public string Annotation { get; set; }

    public IFormFile Poster { get; set; }

    public IFormFile Movie { get; set; }
}
