using Application.Dto;

namespace Application.Services.Interfaces;

public interface IMovieService
{
    public Task<IEnumerable<MovieDto>> GetMoviesAsync(int? limit, int? offset, float? minRating);

    public Task UploadMovieAsync(MovieUploadDto movieInfo);

    public Task<MovieDto?> GetMovieByIdAsync(int id);
}