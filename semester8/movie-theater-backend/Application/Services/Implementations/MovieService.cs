using Application.Services.Interfaces;
using Application.Dto;
using Domain.Repositories;
using Domain.Entities;
using Application.ObjectStorage;

namespace Application.Services.Implementations;

public class MovieService : IMovieService
{
    protected readonly IMovieRepository _movieRepository;
    protected readonly IObjectStorage _objectStorage;

    protected int _expireTime = 60 * 60 * 60;

    public  MovieService(IObjectStorage objectStorage, IMovieRepository movieRepository)
    {
       _objectStorage = objectStorage;
       _movieRepository = movieRepository;
    }

    public async Task<IEnumerable<MovieDto>> GetMoviesAsync(MovieSearchParams parameters)
    {
        IEnumerable<Movie> movies = await _movieRepository.Get(parameters);

        List<Task<MovieDto>> tasks = new();
        
        foreach (var movie in movies)
        {
            tasks.Add(MovieToDtoAsync(movie));
        }

        await Task.WhenAll(tasks);

        List<MovieDto> dtos = new();

        foreach (var task in tasks)
        {
            dtos.Add(task.Result);
        }

        return dtos;
    }

    public async Task<MovieDto?> GetMovieByIdAsync(int id)
    {
        Movie? movie = await _movieRepository.GetById(id);
        if (movie == null) return null;

        return await MovieToDtoAsync(movie);
    }
 
    public async Task UploadMovieAsync(MovieUploadDto movieInfo)
    {
        string movieName = Guid.NewGuid().ToString();
        string imageName = Guid.NewGuid().ToString();

        Task[] tasks = {
            _objectStorage.PutObjectAsync(movieInfo.Movie, ObjectType.Movie, movieName),
            _objectStorage.PutObjectAsync(movieInfo.Image, ObjectType.Image, imageName),
            _movieRepository.Add(new Movie 
            {
                Title = movieInfo.Title,
                Annotation = movieInfo.Annotation,
                MovieObjectName = movieName,
                ImageObjectName = imageName,
                Length = movieInfo.Length,
                Year = movieInfo.Year,
                CountryId = movieInfo.CountryId,
                GenreId = movieInfo.GenreId,
                ScoresSum = (int)(movieInfo.Rating * 10),
                ScoresCount = 10
            })
         };

        await Task.WhenAll(tasks);
        _movieRepository.Save();
    }

    protected async Task<MovieDto> MovieToDtoAsync(Movie movie)
    {

        return new MovieDto 
        {
            Id = movie.Id,
            Title = movie.Title, 
            Annotation = movie.Annotation,
            MovieUrl = await _objectStorage.PresignedGetObjectAsync(ObjectType.Movie, 
                movie.MovieObjectName, _expireTime),
            ImageUrl =  await _objectStorage.PresignedGetObjectAsync(ObjectType.Image, 
                movie.ImageObjectName, _expireTime),
            Rating = (float)(movie.ScoresCount == 0 ? 0 : movie.ScoresSum * 1.0 / movie.ScoresCount),
            Length = movie.Length,
            Year = movie.Year,
            Country = movie.Country.Name,
            Genre = movie.Genre.Name
        };
    }
}
