using Application.Dto;

namespace Application.Services.Interfaces;

public interface IMovieService
{
    public Task<IEnumerable<MovieDto>> GetMoviesAsync(float? minRating);

    public Task UploadMovie(MovieUploadDto movieInfo);
}