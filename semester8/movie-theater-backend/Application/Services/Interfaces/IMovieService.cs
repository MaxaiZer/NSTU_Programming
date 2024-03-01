using Application.Dto;
using Domain.Repositories;

namespace Application.Services.Interfaces;

public interface IMovieService
{
    public Task<IEnumerable<MovieDto>> GetMoviesAsync(MovieSearchParams parameters);

    public Task UploadMovieAsync(MovieUploadDto movieInfo);

    public Task<MovieDto?> GetMovieByIdAsync(int id);
}