using Domain.Entities;

namespace Domain.Repositories;

public interface IMovieRepository
{
    public Task<IEnumerable<Movie>> Get(int? limit, int? offset, float? minRating);

    public Task<Movie?> GetById(int id);

    public Task Add(Movie movie);

    public void Save();
}